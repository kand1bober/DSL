require_relative "encoding"
require_relative "regfile"
require_relative '../../Generic/builder.rb'
require_relative '../../Generic/base.rb'
require 'yaml'

# Разрешаем загрузку нужных классов из YAML
allowed_classes = [
    Symbol,
    SimInfra::Field,
    SimInfra::Var,
    SimInfra::XReg,
    SimInfra::Scope,
    SimInfra::IrStmt
]

OPS = {
    add: '+',
    sub: '-',
    and: '&',
    or: '|',
    xor: '^',

    sll: '<<',
    srl: '>>',
    sra: '>>>',
    slt: '<', 
    sltu: '<',

    mul: '*',
    mulh: '*',
    mulhsu: '*',
    mulhu: '*',

    div: '/',
    divu: '/',
    rem: '%',
    remu: '%',    
}

MAP = OPS.transform_values do |op| 
    ->(dst, a, b) { "\t#{dst} = #{a} #{op} #{b};" }
end

# Загружаем YAML
ir_list = YAML.safe_load(File.read('IR.yaml'), permitted_classes: allowed_classes, aliases: true)

# generate C++
File.open("interpret.cpp", "w") do |f|
    f.puts("#include <cstdint>")
    f.puts("#include <array>")
    f.puts("struct CPU { std::array<uint32_t,32> regs; };\n\n")

    # for each insn from IR tree
    ir_list.each do |insn|
        name = insn[:name].to_s
        params = String.new() 
        insn[:args].each do |arg|
            params << ", num_#{arg.name.to_s}"
        end
        f.puts("void exec_#{name}(CPU &cpu#{params}) {")

        # for each stmt from code tree of this insn
        insn[:code].tree.each do |stmt|
        case stmt.name
            when :getreg
                f.puts("\t#{stmt.oprnds[0]} = cpu.regs[num_#{stmt.oprnds[1].name.to_s}];")
                
            when :setreg
                f.puts("\tcpu.regs[num_#{stmt.oprnds[0].name.to_s}] = #{stmt.oprnds[1]};")
            
            when name.to_sym
                dst = stmt.oprnds[0].name.to_s
                a = stmt.oprnds[1].name.to_s
                b = stmt.oprnds[2].name.to_s
                f.puts(MAP[stmt.name].call(dst, a, b))
                
            when :let
                f.puts("\t#{stmt.oprnds[0].name.to_s} = #{stmt.oprnds[1].name.to_s};")

            when :new_var # var declaration
                f.puts("\tuint32_t #{stmt.oprnds[0].name};")
            end

            else 
        end

        f.puts("}\n\n")
    end
end

puts("C++ interpreter generated in interpret.cpp")
