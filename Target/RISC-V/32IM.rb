require_relative "encoding"
require_relative "regfile"
require_relative "../../Generic/base"

module RV32I
    extend SimInfra
    include SimInfra

    #---------- R ----------
    def self.make_r_alu(name)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r(name.to_s.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { rd[]= rs1.send(name, rs2) } #call for rs1 method with "name", passing rs2 as argument                      
        }
    end
    R_ALU_TYPE_INSNS.each do |name| 
        make_r_alu(name)
    end

    def self.make_r_mul(name, &block_code)
        Instruction(name, XReg(:rd), XReg(:rs1), XReg(:rs2)) {
            encoding *format_r(name.to_s.to_sym, rd, rs1, rs2)
            asm { "#{name} #{rd}, #{rs1}, #{rs2}" }
            code { instance_exec(rd, rs1, rs2, &block_code) }
        }
    end
    make_r_mul(:mul) { |rd, rs1, rs2| 
        rd[]= bit_extract(op_mul(i64(rs1), i64(rs2)), 31, 0) 
    }
    make_r_mul(:mulh) { |rd, rs1, rs2| 
        rd[]= bit_extract(op_mul(i64(rs1), i64(rs2)), 63, 32) 
    }
    make_r_mul(:mulhsu) { |rd, rs1, rs2| 
        rd[]= bit_extract(op_mul(i64(rs1), ui64(rs2)), 63, 32) 
    }
    make_r_mul(:mulhu) { |rd, rs1, rs2| 
        rd[]= bit_extract(op_mul(ui64(rs1), ui64(rs2)), 63, 32) 
    }

    make_r_mul(:div) { |rd, rs1, rs2| 
        rd[]= op_div_signed(rs1, rs2) 
    }
    make_r_mul(:divu) { |rd, rs1, rs2| 
        rd[]= op_div_unsign(rs1, rs2) 
    }
    make_r_mul(:rem) { |rd, rs1, rs2| 
        rd[]= op_rem_signed(rs1, rs2) 
    }
    make_r_mul(:remu) { |rd, rs1, rs2| 
        rd[]= op_rem_unsign(rs1, rs2) 
    }

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
                # You need to write .self, if custom method name conflicts with ruby methods
                # example: and, or, xor
                pc[]= self.and(add(rs1, se(imm, 12)), ~0x1) 
            }                       
        }
    end
    I_JUMP_TYPE_INSNS.each do |name|
        make_i_jump(name)
    end

    def self.make_i_mem(name, &read_mem)
        Instruction(name, XReg(:rd), XReg(:rs1), Imm()) {
            encoding *format_i_mem(name.to_s.to_sym, rd, rs1)
            asm { "#{name} #{rd}, #{imm}(#{rs1})" }
            code {
                addr = var(:addr, :i32) #create variable
                addr[]= add(rs1, se(imm, 12))
                instance_exec(addr, &read_mem) 
            }                   
        }
    end
    # readMem<num> is simulation side / implementation defined
    make_i_mem(:lb)  { |addr| rd[]= se(readMem8(addr),  8) }
    make_i_mem(:lh)  { |addr| rd[]= se(readMem16(addr), 16) }
    make_i_mem(:lw)  { |addr| rd[]= readMem32(addr) }
    make_i_mem(:lbu) { |addr| rd[]= ze(readMem8(addr),  8) }
    make_i_mem(:lhu) { |addr| rd[]= ze(readMem16(addr), 16) }

    #---------- S ----------
    def self.make_s(name, &write_mem)
        Instruction(name, XReg(:rs1), XReg(:rs2), Imm()) {
            encoding *format_s(name.to_s.to_sym, rs1, rs2)
            asm { "#{name} #{rs2}, #{imm}(#{rs1})" }    
            code {
                # send(name, rs1, imm, rs2) 
                addr = var(:addr, :i32) #create variable
                addr[]= add(rs1, se(imm, 12))
                instance_exec(addr, rs2, &write_mem) 
            }
        }
    end
    make_s(:sb) { |addr, rs2|  writeMem8(addr, rs2) }
    make_s(:sh) { |addr, rs2|  writeMem16(addr, rs2) }
    make_s(:sw) { |addr, rs2|  writeMem32(addr, rs2) }

    #---------- B ----------
    def self.make_b(name, cond)
        Instruction(name, XReg(:rs1), XReg(:rs2), Imm(), PC()) {
            encoding *format_b(name.to_s.to_sym, rs1, rs2)
            asm { "#{name} #{rs1}, #{rs2}, #{imm}" }    
            code { 
                pc.add_assign ternary(send(cond, rs1, rs2), se(imm, 13), 0)   
            }
        }
    end

    [{name: :beq, cond: 'equ'}, 
     {name: :bne, cond: 'not_equ'},
     {name: :blt, cond: 'less_signed'}, 
     {name: :bge, cond: 'more_equal_signed'},
     {name: :bltu, cond: 'less_unsign'},
     {name: :bgeu, cond: 'more_equal_unsign'}].each do |insn|
        make_b(insn[:name], insn[:cond])
    end

    #---------- U ----------
    def self.make_u(name, &code_block)
        Instruction(name, XReg(:rd), Imm(), PC()) {
            encoding *format_u(name.to_s.to_sym, rd)
            asm { "#{name} #{rd}, #{imm}" }
            code { 
                instance_exec(rd, imm, pc, &code_block)
            }                       
        }
    end
    make_u(:lui)   { rd[]= op_sll(imm, 12) }
    make_u(:auipc) { rd[]= add(pc, op_sll(imm, 12)) }

    #---------- J ----------
    def self.make_j(name)
        Instruction(name, XReg(:rd), Imm(), PC()) {
            encoding *format_j(name.to_s.to_sym, rd)
            asm { "#{name} #{rd}, #{imm}" }
            code { 
                rd[]= add(pc, 4)
                pc.add_assign se(imm, 21)
            }                       
        }
    end
    J_TYPE_INSNS.each do |name|
        make_j(name)
    end

    def self.make_sys(name, &block_code) 
        Instruction(name) {
            encoding *format_sys(name.to_s.to_sym)
            asm { "#{name}" }
            code { instance_exec(&block_code) }                       
        }
    end

    make_sys(:ecall) { self.raiseException('env_call') }
    # make_sys(:fence) { self.raiseException('env_call') }
    # make_sys(:ebreak) { self.raiseException('ebreak') }
end
