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

    def self.make_i_jump(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm(), PC()) {
            encoding *format_i_jump(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{imm}(#{rs1})" }
            code { send(name, rd, imm, rs1, pc) }                       
        }
    end
    I_JUMP_TYPE_INSNS.each do |name|
        make_i_jump(name)
    end

    def self.make_i_mem(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm(), PC()) {
            encoding *format_i_mem(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{imm}(#{rs1})" }
            code { send(name, rd, imm, rs1, pc) }                       
        }
    end
    I_MEM_TYPE_INSNS.each do |name|
        make_i_mem(name)
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
    def self.make_u(name)
        Instruction(name, XReg(:rd), Imm(), PC()) {
            encoding *format_u(name.to_s.to_sym, rd)
            asm { "#{name} #{rd}, #{imm}" }
            code { rd[]= imm.send(name, pc) }                       
        }
    end
    I_JUMP_TYPE_INSNS.each do |name|
        make_u(name)
    end

    #---------- J ----------
    def self.make_j(name)
        Instruction(name, XReg(:rd), Imm(), PC()) {
            encoding *format_j(name.to_s.to_sym, rd)
            asm { "#{name} #{rd}, #{imm}" }
            code { send(name, rd, imm, pc) }                       
        }
    end
    I_JUMP_TYPE_INSNS.each do |name|
        make_j(name)
    end
end

