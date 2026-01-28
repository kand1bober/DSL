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
    SimInfra::ImmFieldPart,
    SimInfra::Var,
    SimInfra::XReg,
    SimInfra::Imm,
    SimInfra::Scope,
    SimInfra::IrStmt,
    SimInfra::IrExpr,
    SimInfra::Constant,
]

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
    },
    unary: { # --- here are expressions, not statement
        ui8:  'uint8_t', 
        ui16: 'uint16_t', 
        ui32: 'Register', 
        i8:   'int8_t', 
        i16:  'int16_t',
        i32:  'SignedRegister',
        ternary: 'ternary'
    }
}


#return category and string representation
def find_op(sym)
    BASE_OPS.each do |category, mapping|
        return [category, mapping[sym]] if mapping.has_key?(sym)
    end
    nil
end

# op_type - always sym, val_sym - string(watch BASE_OPS)
def interpret_result(code, op_type, op_val)
    puts "1) op_type = #{op_type}\nop_val = #{op_val}"
    str = String.new()
    case op_type 
        when :natural
            dst = get_operand_val(code.oprnds[0])
            a = get_operand_val(code.oprnds[1])
            b = get_operand_val(code.oprnds[2])
            str = "#{dst} = (#{a} #{op_val} #{b})"
        # when :prefix
        #     str = "#{code.oprnds[0].name} = (#{op_val})(#{code.oprnds[1].name})"
        # when :special
        #     case op_val
        #         when 'ternary'
        #             str = "#{get_operand_val(code.oprnds[0])} = ((bool)#{get_operand_val(code.oprnds[1])}) ? 1 : 0"
        #     end
        when :self_realized
            dst = get_operand_val(code.oprnds[0])
            str = "#{dst} = #{op_val}(cpu#{get_call_params(code)})"
    end
    return str
end

# get info about operand. returns string with value
def get_operand_val(oprnd)
    case oprnd
        when SimInfra::Var
            return oprnd.name.to_s
        when SimInfra::Constant
            return oprnd.value.to_s
        when SimInfra::IrExpr
            #recursion untill Var/Const
            op_type, op_val = find_op(oprnd.name.to_sym)
            puts "2) op_type = #{op_type}\nop_val = #{op_val}\n\n"
            if (op_type == :unary)
                case oprnd.name.to_sym
                    when :ternary
                        return "((bool)(#{get_operand_val(oprnd.oprnds[0])}) ? 1 : 0)"
                    else #type castings
                        return "(#{op_val})(#{get_operand_val(oprnd.oprnds[0])})"
                end 
            else 
                raise "Undefined behaviour"    
            end
        when SimInfra::IrStmt

    end
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
        params << ", Register num_#{arg.name.to_s}"
    end

    return params
end

# load YAML
ir_list = YAML.safe_load(File.read('result/IR.yaml'), permitted_classes: allowed_classes, aliases: true)

# generate C++
File.open("result/interpret.cpp", "w") do |f|
    f.puts("#include \"op.h\"\n\n")

    # for each insn from IR tree
    ir_list.each do |insn|
        name = insn[:name].to_s
        f.puts("void exec_#{name}(CPU &cpu#{get_formal_params(insn)}) {")

        puts "  #{name}"
        # for each stmt from code tree of this insn
        insn[:code].tree.each do |code|
        # result = find_op(code.name)
        # puts "#{result}"
        if (code.class == SimInfra::IrStmt)
            case code.name
                when :getimm
                    f.puts("\t#{code.oprnds[0]} = num_#{code.oprnds[1].name.to_s};")
                when :getreg
                    f.puts("\t#{code.oprnds[0]} = cpu.regs[num_#{code.oprnds[1].name.to_s}];")
                when :setreg
                    f.puts("\tcpu.regs[num_#{code.oprnds[0].name.to_s}] = #{code.oprnds[1]};")
                when :let
                    f.puts("\t#{code.oprnds[0].name.to_s} = #{code.oprnds[1].name.to_s};")
                when :new_var
                    f.puts("\tRegister #{code.oprnds[0].name};")
                when :new_const 
                else #special operations
                    if (result = find_op(code.name))
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

puts("C++ interpreter generated in interpret.cpp")
