module SimInfra
    class XReg
        attr_reader :name
        def initialize(name)
            @name = name
            return name
        end

        # String representation for asm output
        def to_s
            @name.to_s
        end
    end
    def XReg(name); XReg.new(name); end

    class Imm
        attr_reader :name, :len
        def initialize()
            @name = :imm
            return name
        end

        def to_s
            return @name.to_s
        end
    end
    def Imm(); Imm.new(); end

    class PC
        attr_reader :name
        def initialize()
            @name = :pc
            return @name
        end

        # String representation for asm output
        def to_s
            @name.to_s
        end
    end
    def PC(); PC.new(); end
end


# MUST HAVE (5 баллов)
# + 1. Убрать избыточность jal/jalr, b<cond> (без if)
# + 2. Интерфейсы памяти ( как с Div/ Rem)
# + 3. Тестирование и рефакторинг декодера
# 4. Тестирование симулятора (все инструкции) (riscv-tests)
# 5. Загрузка ELF

# NICE TO HAVE (6 баллов)
# + 1. Убрать избыточность для памяти
# + 2. Реструктуризация проекта (codegen лежит отдельно, статические -- отдельно)
# 3. RegFile Codegen
# 4. ECALL

# 
# Regfile = [
#     "x0", "ignore_write" / "read_only"
#     "x1"
#     "x0"
#     ...
# 
#     "x17", "a0"
# 
#     "x28"
#     "x29"
#     "x30"
#     "x31"
# ]

# в 32IM можно поменять
# code { rd[]= rs1 name.op rs2 }                      



