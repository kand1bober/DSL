require_relative "encoding"
require_relative "regfile"
require_relative "../../Generic/base"

module RV32I
    extend SimInfra
    include SimInfra

    #---------- R ----------
    def self.make_r_alu(name)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r_alu(name.to_s.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { rd[]= rs1.send(name, rs2) } #call for rs1 method with "name", passing rs2 as argument                      
        }
    end
    R_ALU_TYPE_INSNS.each do |name| 
        make_r_alu(name)
    end

    #---------- I ----------
    def self.make_i_alu(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm()) {
            encoding *format_i_alu(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{rs1}, #{imm}" }
            code { rd[]= rs1.send(name, imm) }                       
        }
    end
    I_ALU_TYPE_INSNS.each do |name|
        make_i_alu(name)
    end

    #---------- S ----------
    

    #---------- B ----------
    def self.make_b(name)
        Instruction(name, XReg(:rs1), XReg(:rs2), Imm(), PC()) {
            encoding *format_b(name.to_s.to_sym, rs1, rs2)
            asm { "#{name} #{rs1}, #{rs2}, #{imm}" }    
            code { send(name, rs1, rs2, imm, pc) }
        }
    end
    B_TYPE_INSNS.each do |name|
        make_b(name)
    end

    #---------- U ----------


    #---------- J ----------

    
end

