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
    prefix: {
        ui8:  'uint8_t', 
        ui16: 'uint16_t', 
        ui32: 'Register', 
        i8:   'int8_t', 
        i16:  'int16_t',
        i32:  'SignedRegister'
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
    special: {
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

# type_sym - always sym, val_sym - string(watch BASE_OPS)
def interpret_result(stmt, type_sym, val)
    str = String.new()
    case type_sym 
        when :natural
            dst = stmt.oprnds[0].name.to_s
            a = stmt.oprnds[1].name.to_s
            b = stmt.oprnds[2].name.to_s
            str = "#{dst} = (#{a} #{val} #{b})"
        when :prefix
            str = "#{stmt.oprnds[0].name} = (#{val})(#{stmt.oprnds[1].name})"
        when :special
            case val
                when 'ternary'
                    str = "#{stmt.oprnds[0].name} = ((bool)#{stmt.oprnds[1].name}) ? 1 : 0"
            end
        when :self_realized
            dst = stmt.oprnds[0].name.to_s
            str = "#{dst} = #{val}(cpu#{collect_call_params(stmt)})"
    end

    return str
end

def collect_call_params(stmt) 
    params = String.new() 
    stmt[:oprnds][1..-1].each do |oprnd|
        case oprnd
            when SimInfra::Var
                if oprnd.name[0] != '_'
                    params << ", num_#{oprnd.name}"
                else 
                    params << ", #{oprnd.name}"       
                end                         
            when SimInfra::Constant
                params << ", #{oprnd.value}"
        end
    end

    return params
end

def collect_formal_params(insn)
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
        f.puts("void exec_#{name}(CPU &cpu#{collect_formal_params(insn)}) {")

        # for each stmt from code tree of this insn
        insn[:code].tree.each do |stmt|
        # result = find_op(stmt.name)
        # puts "#{result}"
        case stmt.name
            when :getimm
                f.puts("\t#{stmt.oprnds[0]} = num_#{stmt.oprnds[1].name.to_s};")
            when :getreg
                f.puts("\t#{stmt.oprnds[0]} = cpu.regs[num_#{stmt.oprnds[1].name.to_s}];")
            when :setreg
                f.puts("\tcpu.regs[num_#{stmt.oprnds[0].name.to_s}] = #{stmt.oprnds[1]};")
            when :let
                f.puts("\t#{stmt.oprnds[0].name.to_s} = #{stmt.oprnds[1].name.to_s};")
            when :new_var
                f.puts("\tRegister #{stmt.oprnds[0].name};")
            when :new_const
            else 
                if (result = find_op(stmt.name))
                    f.puts("\t#{interpret_result(stmt, *result)};")                
                else 
                    raise("Unknown statement in code tree: #{stmt.name}")
                end
            end
        end

        f.puts("}\n\n")
    end
end

puts("C++ interpreter generated in interpret.cpp")
