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
    REGISTER_DATA_TYPE = "Register"
    
    def self.generate_decoder_file(tree, ir)
        # collect all incstructions for declarations
        declarations = []
        collect_instructions(tree, declarations)
        instructions = declarations.uniq

        # genarate .h file
        generate_header_file(instructions, ir)
        
        # genarate .cpp file
        generate_cpp_file(tree, instructions, ir)
        
        puts "Decoder generated:"
        puts "  - decoder.cpp"
        puts "  - decoder.h"
    end
    
    private
    
    def self.generate_cpp_file(tree, instructions, ir)
        @output = []
        
        @output << "// Auto-generated decoder from YAML tree"
        # @output << "#include <functional>"
        # @output << "#include <tuple>"
        # @output << "#include <utility>"
        @output << "#include \"op.h\""
        @output << ""
        @output << "// Main decoder implementation"
        @output << "DecodedOperation decode(SPU& spu, #{REGISTER_DATA_TYPE} insn) {"
        @output << INDENT + "// Start decoding from the root"
        generate_switch_statement(tree, ir,  1, "insn")
        # @output << INDENT + "return 0;"
        @output << "}"
        
        File.write('result/decoder.cpp', @output.join("\n"))
    end
      
    def self.generate_header_file(instructions, ir)
        output = []
        
        output << "#ifndef DECODER_HEADER"
        output << "#define DECODER_HEADER"
        output << ""
        output << "#include <cstdint>"
        output << "#include <stdexcept>"
        output << "#include <functional>"
        output << ""
        output << "class SPU;"
        output << ""
        output << "template<typename... Args>\n" +
                    "using SPUFunctionPtr = void(*)(SPU&, Args...);\n\n" +
                    "using DecodedOperation = std::function<void(SPU&)>;\n\n" +
                    "template<typename... Args>\n" +
                    "DecodedOperation make_spu_operation(SPUFunctionPtr<Args...> func, Args... args) {\n" +
                    "\treturn [func, ...args = std::forward<Args>(args)](SPU& spu) mutable {\n" +
                    "\t\tfunc(spu, std::forward<Args>(args)...);\n" + 
                    "\t};\n" +
                    "}\n\n" +
                    "DecodedOperation decode(SPU& spu, #{REGISTER_DATA_TYPE} insn);\n"
        output << "#endif"
        
        File.write('result/decoder.h', output.join("\n"))
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

            args_num = 0
            args.each do |arg| # past args in correct order
                next if arg.name == :pc
                field = fields.find { |field| field[:name] == arg.name} # find field with name of this arg 
                
                spaces = " " * "return  make_spu_operation(".length # arguments on different lines
                arg_values << ",\n#{case_indent + INDENT}#{spaces}"
                case arg.name 
                    when :rd, :rs1, :rs2
                        width = field[:from] - field[:to] + 1
                        arg_values << "(#{var_name} >> #{field[:to]}) & ((1 << #{width}) - 1)"
                        args_num += 1
                    when :imm
                        arg_values << "#{assemble_immediate(field.parts, var_name)}"
                        args_num += 1
                end
            end
            # @output << case_indent + INDENT + "exec_#{child}(spu#{arg_values});"
            @output << case_indent + INDENT + "return  make_spu_operation(exec_#{child}#{arg_values});"

        elsif child.is_a?(Hash) # Subtree - recursive call
            generate_switch_statement(child, ir, indent_level + 2, var_name)
        end
        
        # @output << case_indent + INDENT + "break;"
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
    
    generate_decoder_file(tree, ir)
end
