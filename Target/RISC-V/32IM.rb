require_relative "encoding"
require_relative "regfile"
require_relative "../../Generic/base"

module RV32I
    extend SimInfra
    include SimInfra

    #---------- R ----------
    def self.make_r(name)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r(name.to_s.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { rd[]= rs1.send(name, rs2) } #call for rs1 method with "name", passing rs2 as argument                      
        }
    end
    R_TYPE_INSNS.each do |name| 
        make_r(name)
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
    
    def self.make_i_shift(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm()) {
            encoding *format_i_shift(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{rs1}, #{imm}" }
            code { rd[]= rs1.send(name, imm) }                       
        }
    end
    I_SHIFT_TYPE_INSNS.each do |name|
        make_i_shift(name)
    end

    def self.make_i_jump(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm(), PC()) {
            encoding *format_i_jump(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{imm}(#{rs1})" }
            code { 
                rd[]= add(pc, 4)
                # pc[]= send(:and, add(rs1, se(imm, 12)), ~0x1)
                pc[]= self.and(add(rs1, se(imm, 12)), ~0x1)
            }                       
        }
    end
    I_JUMP_TYPE_INSNS.each do |name|
        make_i_jump(name)
    end

    def self.make_i_mem(name)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm()) {
            encoding *format_i_mem(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{imm}(#{rs1})" }
            # code { rd[]= rs1.send(name, imm) }
            code {
                # addr = rs1 + offset 
                # data = readMem(addr); # simulation side / implementation defined  
                # rd.write(data)
            }                   
        }
    end
    I_MEM_TYPE_INSNS.each do |name|
        make_i_mem(name)
    end

    #---------- S ----------
    def self.make_s(name)
        Instruction(name, XReg(:rs1), XReg(:rs2), Imm()) {
            encoding *format_s(name.to_s.to_sym, rs1, rs2)
            asm { "#{name} #{rs2}, #{imm}(#{rs1})" }    
            code { send(name, rs1, imm, rs2) }
        }
    end
    S_TYPE_INSNS.each do |name|
        make_s(name)
    end

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
    U_TYPE_INSNS.each do |name|
        make_u(name)
    end

    #---------- J ----------
    def self.make_j(name)
        Instruction(name, XReg(:rd), Imm(), PC()) {
            encoding *format_j(name.to_s.to_sym, rd)
            asm { "#{name} #{rd}, #{imm}" }
            code { 
                rd[]= add(pc, 4)
                pc.add_assign se(op_sll(imm, 1), 21)
            }                       
        }
    end
    J_TYPE_INSNS.each do |name|
        make_j(name)
    end
end

