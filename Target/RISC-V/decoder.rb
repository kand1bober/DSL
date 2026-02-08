require 'yaml'

module Decoder
    @allowed_classes = [
        Symbol,
        SimInfra::Field,
        SimInfra::ImmParts,
        SimInfra::Var,
        SimInfra::XReg,
        SimInfra::Imm,
        SimInfra::Scope,
        SimInfra::IrStmt,
        SimInfra::IrExpr,
        SimInfra::Constant,
        SimInfra::PC,
    ]   

    INDENT = "    "
    
    def self.generate_decoder_files(tree, ir, base_name)
        # collect all incstructions for declarations
        declarations = []
        collect_instructions(tree, declarations)
        instructions = declarations.uniq
        
        # genarate .hpp file
        generate_header_file(instructions, ir, "#{base_name}.hpp")
        
        # genarate .cpp file
        generate_cpp_file(tree, instructions, ir, "#{base_name}.cpp")
        
        puts "Decoder generated:"
        puts "  - #{base_name}.hpp (header with declarations)"
        puts "  - #{base_name}.cpp (implementation)"
    end
    
    private
    
    def self.generate_header_file(instructions, ir, output_file)
        output = []
        
        output << "#ifndef DECODER_HPP"
        output << "#define DECODER_HPP"
        output << ""
        output << "#include <cstdint>"
        output << "#include <stdexcept>"
        output << "#include \"op.h\""
        output << ""
        output << "// Execution functions declarations"
        instructions.each do |insn_name|
            args = get_instruction_fields_and_args(ir, insn_name.to_sym)[:args]
            params = String.new()
            args.each do |arg|
                if (arg.name != :pc)
                    params << ", #{arg.name.to_s}"
                end        
            end
            output << "void exec_#{insn_name}(SPU& spu#{params});"
        end
        output << ""
        output << "// Main decoder function"
        output << "uint32_t decode_and_execute(SPU& spu, uint32_t insn);"
        output << ""
        output << "#endif // DECODER_HPP"
        
        File.write(output_file, output.join("\n"))
    end
    
    def self.generate_cpp_file(tree, instructions, ir, output_file)
        @output = []
        
        @output << "// Auto-generated decoder from YAML tree"
        @output << "#include \"#{File.basename(output_file, '.cpp')}.hpp\""
        @output << ""
        
        @output << "// Main decoder implementation"
        @output << "uint32_t decode_and_execute(SPU& spu, uint32_t insn) {"
        @output << INDENT + "// Start decoding from the root"
        generate_switch_statement(tree, ir,  1, "insn")
        @output << INDENT + "return 0;"
        @output << "}"
        
        File.write(output_file, @output.join("\n"))
    end
    
    def self.collect_instructions(node, instructions)
        if node.is_a?(Hash)
            if node[:nodes]
                node[:nodes].each_value do |child|
                if child.is_a?(String) || child.is_a?(Symbol)
                    # it is a leaf - instruction
                    instructions << child.to_s
                elsif child.is_a?(Hash)
                    # it is subtree
                    collect_instructions(child, instructions)
                end
                end
            end
        end
    end
    
    def self.generate_switch_statement(node, ir, indent_level, var_name)
        switch_indent = INDENT * indent_level
        case_indent = INDENT * (indent_level + 1)

        # Defining a mask and a shift to extract the bits
        msb = node[:range][0]
        lsb = node[:range][1]
        width = msb - lsb + 1
        
        @output << switch_indent + "// Extract bits [#{msb}:#{lsb}] (width: #{width})"
        @output << switch_indent + "uint32_t field_#{msb}_#{lsb} = (#{var_name}) & (0x#{( (1 << width) - 1).to_s(16)} << #{lsb});"
        @output << switch_indent + "switch (field_#{msb}_#{lsb}) {"
        
        node[:nodes].each do |key, child|
        @output << case_indent + "case 0x#{key.to_s(16)}: {"
        
        if child.is_a?(String) || child.is_a?(Symbol) # Leaf
            arg_values = String.new()
            fields, args = get_instruction_fields_and_args(ir, child).values_at(:fields, :args)

            args.each do |arg| # past args in correct order
                next if arg.name == :pc
                field = fields.find { |field| field[:name] == arg.name} # find field with name of this arg 
                
                spaces = " " * "exec_#{child}(".length # arguments on different lines
                arg_values << ",\n#{case_indent + INDENT}#{spaces}"
                case arg.name 
                    when :rd, :rs1, :rs2
                        width = field[:from] - field[:to] + 1
                        arg_values << "(#{var_name} >> #{field[:to]}) & ((1 << #{width}) - 1)"
                    when :imm
                        arg_values << "#{assemble_immediate(field.parts, var_name)}"
                end
            end
            @output << case_indent + INDENT + "exec_#{child}(spu#{arg_values});"

        elsif child.is_a?(Hash) # Subtree - recursive call
            generate_switch_statement(child, ir, indent_level + 2, var_name)
        end

        @output << case_indent + INDENT + "break;"
        @output << case_indent + "}"
    end
        
        @output << case_indent + "default:"
        @output << case_indent + INDENT + "throw std::runtime_error(\"Unknown insn: 0x\" + std::to_string(insn));"
        @output << switch_indent + "}"
    end

    # Find instruction in IR by name
    def self.find_instruction_by_name(instructions, name)
        instructions.find { |insn| insn[:name] == name }
    end

    # Get instruction fields
    def self.get_instruction_fields_and_args(instructions, name)
        insn = find_instruction_by_name(instructions, name)
        insn ? {fields: insn[:fields], args: insn[:args]} : nil
    end

    def self.assemble_immediate(parts, var_name)
        # begin from 0
        result = "0"
        
        parts.each do |part|
            insn_from = part[:in_insn][:from]
            insn_to = part[:in_insn][:to]
            imm_from = part[:in_imm][:from]
            imm_to = part[:in_imm][:to]
            
            insn_width = insn_from - insn_to + 1
            imm_width = imm_from - imm_to + 1
            
            if part[:replicate]
                # take a single-bit and replicate it to its full width
                if insn_width == 1
                    result = "(#{result}) | ((((#{var_name} >> #{insn_to}) & 1) ? ((1 << #{imm_width}) - 1) : 0) << #{imm_to})"
                else
                    raise "Replication only supported for single-bit sources"
                end
            else
                # copying a range
                if insn_width == imm_width
                    mask = "(1 << #{insn_width}) - 1"
                    result = "(#{result}) | (((#{var_name} >> #{insn_to}) & #{mask}) << #{imm_to})"
                else
                    raise "Different width of immediate part in instruction and immediate"
                end
            end
        end

        return result
    end
end

module Decoder
    # load decode tree and IR
    tree = YAML.load_file('result/decode_tree.yaml')
    ir = YAML.load_file('result/IR.yaml', permitted_classes: @allowed_classes, aliases: true)
    
    generate_decoder_files(tree, ir, 'result/decoder')
end
