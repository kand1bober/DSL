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
    SimInfra::Var,
    SimInfra::XReg,
    SimInfra::Scope,
    SimInfra::IrStmt,
    SimInfra::Constant,
]

BASE_OPS = {
    self: [:*, :/, :%, :<<, :>>, :<, :>, :>=, :<=, :==],
    string: [:'>>>', :'!='],
    natural: {
        add: '+',
        sub: '-',
        and: '&',
        or:  '|',
        xor: '^', 
    },    
    prefix: [:ui8, :ui16, :ui32], #TODO: как реализовать ternary, ui8/16/32 без вызова функции, а просто в строку
    self_realized: {
        se: 'sign_extend',
        ze: 'zero_extend',

        bit_extract: 'bit_extract',
    }
}

def find_op(sym) 
    db = BASE_OPS #only for shorter name; causes changing of constant, if changing db 
    # Check arrays
    return [:self, sym] if db[:self].include?(sym)
    return [:string, sym] if db[:string].include?(sym)
    return [:prefix, sym] if db[:prefix].include?(sym)
    
    # Check hash
    return [:natural, db[:natural][sym]] if db[:natural].has_key?(sym)
    return [:self_realized, db[:self_realized][sym]] if db[:self_realized].has_key?(sym)
    
    return nil
end

# type_sym - always sym, val_sym - could be a sym or string(watch BASE_OPS)
def interpret_result(stmt, type_sym, val_sym)
    str = String.new()
    case type_sym 
        when :self, :string, :natural
            case type_sym
                when :self
                    op = val_sym.to_s
                when :string
                    op = val_sym.to_s[1,-2] #throwing out ''
                when :natural
                    op = val_sym
            end
            dst = stmt.oprnds[0].name.to_s
            a = stmt.oprnds[1].name.to_s
            b = stmt.oprnds[2].name.to_s
            str = "#{dst} = #{a} #{op} #{b}"
        when :prefix

        when :self_realized
            dst = stmt.oprnds[0].name.to_s

            str = "#{dst} = #{val_sym}(cpu#{collect_call_params(stmt)})"
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
        params << ", uint32_t num_#{arg.name.to_s}"
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
            when :getreg
                f.puts("\t#{stmt.oprnds[0]} = cpu.regs[num_#{stmt.oprnds[1].name.to_s}];")
            when :setreg
                f.puts("\tcpu.regs[num_#{stmt.oprnds[0].name.to_s}] = #{stmt.oprnds[1]};")
            when :let
                f.puts("\t#{stmt.oprnds[0].name.to_s} = #{stmt.oprnds[1].name.to_s};")
            when :new_var # var declaration
                f.puts("\tuint32_t #{stmt.oprnds[0].name};")
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
