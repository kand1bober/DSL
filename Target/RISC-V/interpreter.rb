require_relative "encoding"
require_relative "regfile"
require_relative '../../Generic/builder.rb'
require_relative '../../Generic/base.rb'
require_relative '../../Generic/scope.rb'
require 'yaml'

# Разрешаем загрузку нужных классов из YAML
allowed_classes = [
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

REGISTER_DATA_TYPE = "Register"

BASE_OPS = {
    natural: {
        add: '+',
        sub: '-',
        and: '&',
        or:  '|',
        xor: '^', 

        op_mul: '*',

        op_sll: '<<',
        op_srl: '>>',
        
        equ: '==',
        not_equ: '!=',
    },    
    self_realized: {
        op_div_signed: 'div_signed',
        op_div_unsign: 'div_unsign',
        op_rem_signed: 'rem_signed',
        op_rem_unsign: 'rem_unsign',
        
        se: 'sign_extend',
        ze: 'zero_extend',
        
        bit_extract: 'bit_extract',
        op_sra: 'op_sra',
        
        less_signed: 'less_signed',
        less_unsign: 'less_unsign',
        more_equal_signed: 'more_equal_signed',
        more_equal_unsign: 'more_equal_unsign',

        readMem8: 'readMem8',
        readMem16: 'readMem16',
        readMem32: 'readMem32',
        
        writeMem8: 'writeMem8',
        writeMem16: 'writeMem16',
        writeMem32: 'writeMem32',
    },
    special: {
        ternary: 'ternary',
        cond_op: 'if',
    },
    unary: { # --- here are expressions, not statement
        ui8:  'uint8_t', 
        ui16: 'uint16_t', 
        ui32: REGISTER_DATA_TYPE, 
        i8:   'int8_t', 
        i16:  'int16_t',
        i32:  'int32_t',
    },
}
    
#return category and string representation
def find_op(sym)
    BASE_OPS.each do |category, mapping|
        # puts "#{category}, #{mapping[sym]}"
        return [category, mapping[sym]] if mapping.has_key?(sym)
    end
    nil
end

# op_type - always sym, op_val - string(watch BASE_OPS)
def interpret_result(code, op_type, op_val)
    str = String.new()
    # puts "#{op_type}, #{op_val}"
    case op_type 
        when :natural
            dst = get_operand_val(code.oprnds[0])
            a = get_operand_val(code.oprnds[1])
            b = get_operand_val(code.oprnds[2])
            str = "#{dst} = (#{a} #{op_val} #{b})"
        when :special
            case op_val.to_sym
                when :ternary 
                    str = "#{get_operand_val(code.oprnds[0])} = " + 
                           "((bool)#{get_operand_val(code.oprnds[1])}) ? " + 
                           "(#{get_operand_val(code.oprnds[2])}) : " + 
                           "(#{get_operand_val(code.oprnds[3])})"
                when :if
                    str = "#{op_val} ((bool)#{get_operand_val(code.oprnds[0])}) {\n" +
                          "\t#{get_stmt_val(code.oprnds[1])}\n" +  
                          "\t}"
            end
        when :self_realized
            dst = get_operand_val(code.oprnds[0])
            str = "#{dst} = #{op_val}(spu#{get_call_params(code)})"
    end
    return str
end

# get info about operand. returns string with value
def get_operand_val(oprnd)
    # puts "\t#{oprnd}"
    case oprnd
        when SimInfra::Var
            return oprnd.name.to_s
        when SimInfra::Constant
            return oprnd.value.to_s
        when SimInfra::IrExpr
            #recursion untill Var/Const
            op_type, op_val = find_op(oprnd.name.to_sym)
            # puts "\t\t#{op_type}, #{op_val}"
            if (op_type == :unary)
                return "(#{op_val})(#{get_operand_val(oprnd.oprnds[0])})"
            elsif (op_type == :self_realized)   
                return "#{op_val}(spu, #{get_operand_val(oprnd.oprnds[0])})"
            else 
                raise "Undefined behaviour"    
            end
    end
end

# returns string 
def get_stmt_val(stmt)
    str = String.new()
    case stmt.name
        when :let
            str = "\t#{get_operand_val(stmt.oprnds[0])} = #{get_operand_val(stmt.oprnds[1])};"
        else 
            raise "Unknown statemnt in 'get_stmt_val': #{stmt.name}"
    end
    return str
end

def get_call_params(stmt) 
    params = String.new() 
    stmt[:oprnds][1..-1].each do |oprnd|
        params << ", #{get_operand_val(oprnd)}"
    end
    return params
end

def get_formal_params(insn)
    params = String.new() 
    insn[:args].each do |arg|
        if (arg.name != :pc)
            params << ", #{REGISTER_DATA_TYPE} par_#{arg.name.to_s}"
        end        
    end
    return params
end

def insert_code(filename, strings)
    start_marker = "// Begin of auto-generated prototypes"
    end_marker = "// End of auto-generated prototypes"
    
    content = File.read(filename)
    
    # check, that strings is an array of strings
    code = Array(strings).join("\n")
    
    # pattern for searching markers
    pattern = /(#{Regexp.escape(start_marker)}).*?(#{Regexp.escape(end_marker)})/m
    
    if content =~ pattern
        # Replacing the existing block
        replacement = "#{start_marker}\n#{code}\n#{end_marker}"
        new_content = content.gsub(pattern, replacement)
    else
        # adding new block to the end
        new_content = content + "\n#{start_marker}\n#{code}\n#{end_marker}\n"
    end
    
    File.write(filename, new_content)
end

# load YAML
ir_list = YAML.safe_load(File.read('result/generated/IR.yaml'), permitted_classes: allowed_classes, aliases: true)

# modify header file
output = []
output << "\t// Execution functions declarations"
ir_list.each do |insn|
    params = String.new()
    name = insn[:name].to_s
    insn[:args].each do |arg|
        next if arg.name == :pc
        params << ", #{REGISTER_DATA_TYPE} #{arg.name.to_s}"
    end
    output << "\tvoid exec_#{name}(SPU& spu#{params});"
end
output << ""
insert_code("result/op.h", output)

# generate C++
File.open("result/generated/interpret.cpp", "w") do |f|
    f.puts("#include \"op.h\"\n\n")

    # for each insn from IR tree
    ir_list.each do |insn|
        name = insn[:name].to_s
        f.puts("void exec_#{name}(SPU &spu#{get_formal_params(insn)}) {")
        f.puts("\tstd::cout << \"#{name}\" << std::endl;")
            # for each stmt from code tree of this insn 
            insn[:code].tree.each do |code| # code is either stmt of expr
            if (code.class == SimInfra::IrStmt)
                case code.name
                    when :getpc
                        f.puts("\t#{code.oprnds[1]} = spu.cpu.#{code.oprnds[0].name.to_s};")                                
                    when :getimm 
                        f.puts("\t#{code.oprnds[0]} = par_#{code.oprnds[1].name.to_s};") 
                    when :getreg
                        f.puts("\t#{code.oprnds[0]} = spu.cpu.regs[par_#{code.oprnds[1].name.to_s}];")
                    when :let
                        f.puts("\t#{get_operand_val(code.oprnds[0])} = #{get_operand_val(code.oprnds[1])};")
                    when :new_var
                        f.puts("\t#{REGISTER_DATA_TYPE} #{code.oprnds[0].name};")
                    when :new_const 
                        # skip
                    when :setreg
                        f.puts("\tspu.cpu.regs[par_#{code.oprnds[0].name.to_s}] = #{code.oprnds[1]};")
                    when :setpc
                        f.puts("\tspu.cpu.#{code.oprnds[0].name.to_s} = #{code.oprnds[1]};")
                    else # special operations
                        if (result = find_op(code.name.to_sym))
                            f.puts("\t#{interpret_result(code, *result)};")                
                        else 
                            raise("Unknown statement in code tree: #{code.name}")
                        end
                end
            elsif (code.class == SimInfra::IrExpr)
                # skip
            else 
                puts "Unknown piece of code, it is not a statement nor expression"
            end
                
        end
        f.puts("}\n\n")
    end
end

puts("C++ interpreter generated in 'result/generated/interpret.cpp'")
