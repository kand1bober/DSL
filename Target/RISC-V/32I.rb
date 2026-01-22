require_relative "encoding"
require_relative "regfile"
require_relative "../../Generic/base"

module RV32I
    extend SimInfra

    #---------- R ----------
    def self.make_r_insn(name)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r_alu(name.to_s.downcase.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { rd[]= rs1.send(name, rs2) } #call for rs1 method with "name", passing rs2 as argument                      
        }
    end

    R_ALU_INSNS = [
        :add, :sub, :or, :and, :xor,
        :sll, :slt, :sltu, :srl, :sra,
        :mul, :mulh, :mulhsu, :mulhu,
        :div, :divu, :rem, :remu
    ]

    R_ALU_INSNS.each do |name| 
        make_r_insn(name)
    end

    #---------- I ----------
    # I_ALU_INSNS

    #---------- S ----------


    #---------- B ----------


    #---------- U ----------


    #---------- J ----------

end

