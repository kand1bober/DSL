require_relative "encoding"
require_relative "regfile"
require_relative "../../Generic/base"

module RV32I
    extend SimInfra

    R_INSNS = [
        :add, :sub, :or, :and, :xor,
        # :sll, :slt, :sltu, :srl, :sra,
        # :mul, :mulh, :mulhsu, :mulhu,
        # :div, :divu, :rem, :remu
    ]
      

    def self.make_r_insn(name)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r_alu(name.to_s.downcase.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { rd[]= rs1.send(name, rs2) }                        
        }
    end

    # Instruction(:ADD, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
    #     encoding *format_r_alu(:add, rd, rs1, rs2)
    #     asm { "ADD #{rd}, #{rs1}, #{rs2}" }
    #     code { rd[]= rs1 + rs2 }
    # }

    # Instruction(:SUB, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
    #     encoding *format_r_alu(:add, rd, rs1, rs2)
    #     asm { "SUB #{rd}, #{rs1}, #{rs2}" }
    #     code { rd[]= rs1 - rs2 }
    # }
    
    R_INSNS.each do |name| 
        make_r_insn(name)
    end

end

