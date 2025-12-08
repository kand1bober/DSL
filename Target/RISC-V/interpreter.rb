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

MAP = {
    add: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} + #{b};" },
    sub: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} - #{b};" },
    and: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} & #{b};" },
    or: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} | #{b};" },
    xor: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} ^ #{b};" },
    sll: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} << #{b};" },
    sra: ->(dst, a, b) { "\tuint32_t #{dst} = #{a} >> #{b};" },
  }  

# Загружаем YAML
ir_list = YAML.safe_load(File.read('IR.yaml'), permitted_classes: allowed_classes, aliases: true)

# generate C++
File.open("interpret.cpp", "w") do |f|
    f.puts "#include <cstdint>"
    f.puts "#include <array>"
    f.puts "struct CPU { std::array<uint32_t,32> regs; };"
    f.puts

    # for each insn from IR tree
    ir_list.each do |insn|
        name = insn[:name].to_s
        f.puts "void exec_#{name}(CPU &cpu) {"

        # for each stmt from description of insn
        insn[:code].tree.each do |stmt|
        case stmt.name
            when :getreg
                f.puts "\tuint32_t #{stmt.oprnds[0]} = cpu.regs[#{stmt.oprnds[1].name.to_s}];"
            
            when :setreg
                f.puts "\tcpu.regs[#{stmt.oprnds[0].name.to_s}] = #{stmt.oprnds[1]};"
            
            when :add, :sub, :and, :or, :xor
                dst = stmt.oprnds[0].name.to_s
                a = stmt.oprnds[1].name.to_s
                b = stmt.oprnds[2].name.to_s
                f.puts MAP[stmt.name].call(dst, a, b)
                
            when :let
                # простая переменная-подстановка
                # TODO: что такое let
            when :new_var # var declaration
                f.puts "\tuint32_t #{stmt.oprnds[0].name};"
            end
        end

        f.puts "}"
        f.puts
    end
end

puts "C++ interpreter generated in interpret.cpp"
