require_relative "../../Generic/base"

module SimInfra
    #-------------- Field separations and some field values ----------------

    #-------------- RV32IM --------------
    def format_r(funct3, funct7, rd, rs1, rs2, opcode)
        return :R, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            field(rs2.name, 24, 20, :reg),
            field(:opcode, 6, 0, opcode),
            field(:funct7, 31, 25, funct7),
            field(:funct3, 14, 12, funct3),
        ]
    end

    def format_i(rs1, funct3, rd, opcode) 
        return :I, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            imm_field_part(31, 20),
            field(:funct3, 14, 12, funct3),
            field(:opcode, 6, 0, opcode),
        ]
    end

    def format_s_b(funct3, rs1, rs2, opcode)
        return :R, [
            imm_field_part(11, 7, :lo),
            field(rs1.name, 19, 15, :reg),
            field(rs2.name, 24, 20, :reg),
            imm_field_part(31, 25, :hi),
            field(:opcode, 6, 0, opcode),   
            field(:funct3, 14, 12, funct3),
        ]
    end

    def format_u_j(rd, opcode)
        return :R, [
            field(rd.name, 11, 7, :reg),
            imm_field_part(31, 12),
            field(:opcode, 6, 0, opcode),
        ]
    end
    
    #-------------- funct3, funct7 values  ----------------
    #----- R -----
    def format_r_alu(name, rd, rs1, rs2)
        funct3, funct7 =
        {
            add:  [0, 0],
            sub:  [0, 1 << 5],
            sll:  [1, 0],
            slt:  [2, 0],
            sltu: [3, 0],
            xor:  [4, 0],
            srl:  [5, 0],
            sra:  [6, 1 << 5],
            or:   [7, 0],
            and:  [8, 0]
        }[name]
        format_r(funct3, funct7, rd, rs1, rs2, 0b0110011)
    end
    
    #----- I -----
    def format_i_alu(name, rd, rs1)
        funct3 =
        {
            addi:  [0],
            slti:  [2],
            sltui: [3],
            xori:  [4],
            ori:   [6],
            andi:  [7],
        }[name]
        format_i(rs1, funct3, rd, 0b0010011)
    end

    def format_i_mem(name, rd, rs1) 
        funct3 =
        {
            lb:  [0],
            lh:  [1],
            lw:  [2],
            lbu: [4],
            lhu: [5],
        }[name]
        format_i(rs1, funct3, rd, 0b0000011)
    end

    def format_i_shift(name, rs1, rd) 
        funct3, funct7 = 
        {
            slli:  [1, 0],
            srli:  [5, 0],
            srai:  [5, 1 << 5],
        }[name]

        return :I, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            imm_field_part(24, 20),
            field(:funct3, 14, 12, funct3),
            field(:funct7, 31, 25, funct7),
            field(:opcode, 6, 0, 0b0010011),
        ]
    end

    def format_i_jump(name, rs1, rd)
        funct3 = 
        {
            jalr: [0],
        }
        format_i(rs1, funct3, rd, 0b1100111)
    end

    #----- S -----
    def format_s(name, rs1, rs2) 
        funct3 = {
            sb: [0],
            sh: [1],
            sw: [2],
        }[name]
        format_s_b(funct3, rs1, rs2, 0b0100011)
    end

    #----- B -----
    def format_b(name, rs1, rs2)
        funct3 = {
            beq:  [0],
            bne:  [1],
            blt:  [4],
            bge:  [5],
            bltu: [6],
            bgeu: [7],
        }[name]
        format_s_b(funct3, rs1, rs2, 0b1100011)
    end

    #----- U -----
    def format_u(name, rd) 
        opcode = 
        {   
            lui:  [0b0110111], 
            auipc: [0b0010111],
        }[name]
        format_u_j(rd, opcode)
    end

    #----- J -----
    def format_j(name, rd) 
        format_u_j(rd, 0b1101111)
    end

end
