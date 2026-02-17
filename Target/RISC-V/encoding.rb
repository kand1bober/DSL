require_relative "../../Generic/base"

module SimInfra
    #-------------- Field separations and some field values ----------------

    #-------------- RV32IM --------------
    def format_r(name, rd, rs1, rs2)
        pair =
        {
            add:  [0, 0],
            sub:  [0, 1 << 5],
            sll:  [1, 0],
            slt:  [2, 0],
            sltu: [3, 0],
            xor:  [4, 0],
            srl:  [5, 0],
            sra:  [5, 1 << 5],
            or:   [6, 0],
            and:  [7, 0],

            mul:    [0, 1], 
            mulh:   [1, 1],
            mulhsu: [2, 1],
            mulhu:  [3, 1],

            div:    [4, 1],
            divu:   [5, 1],
            rem:    [6, 1],
            remu:   [7, 1]
        }[name]

        funct3, funct7 = pair[0], pair[1]
        opcode = 0b0110011

        opcode_field = field(:opcode, 6, 0, opcode)
        funct7_field = field(:funct7, 31, 25, funct7)
        funct3_field = field(:funct3, 14, 12, funct3)
    
        return :R, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            field(rs2.name, 24, 20, :reg),
            opcode_field,
            funct7_field,
            funct3_field,
        ], lead_bits([opcode_field, funct3_field, funct7_field])
    end
    
    def format_i(rs1, funct3, rd, opcode) 
        funct3_field = field(:funct3, 14, 12, funct3)
        opcode_field = field(:opcode, 6, 0, opcode)

        return :I, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 31, to: 31}, in_imm: {from: 31, to: 11}, replicate: true},
                        {in_insn: {from: 30, to: 20}, in_imm: {from: 10, to: 0},  replicate: false}
                       ],
                       shift: 0}),
            funct3_field,   
            opcode_field,   
        ], lead_bits([opcode_field, funct3_field])
    end

    #----- S -----
    def format_s(name, rs1, rs2)
        funct3 = {
            sb: 0,
            sh: 1,
            sw: 2,
        }[name]

        funct3_field= field(:funct3, 14, 12, funct3)
        opcode_field= field(:opcode, 6, 0, 0b0100011)   

        return :S, [
            field(rs1.name, 19, 15, :reg),
            field(rs2.name, 24, 20, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 31, to: 31}, in_imm: {from: 31, to: 11}, replicate: true},
                        {in_insn: {from: 30, to: 25}, in_imm: {from: 10, to: 5},  replicate: false}, 
                        {in_insn: {from: 11, to: 8}, in_imm: {from: 4, to: 1},    replicate: false},
                        {in_insn: {from: 7, to: 7}, in_imm: {from: 0, to: 0},     replicate: false}
                       ],
                       shift: 0}),
            funct3_field,
            opcode_field,   
        ], lead_bits([opcode_field, funct3_field])
    end

    #----- B -----
    def format_b(name, rs1, rs2)
        funct3 = {
            beq:  0,
            bne:  1,
            blt:  4,
            bge:  5,
            bltu: 6,
            bgeu: 7,
        }[name]

        funct3_field= field(:funct3, 14, 12, funct3)
        opcode_field= field(:opcode, 6, 0, 0b1100011)   

        return :B, [
            field(rs1.name, 19, 15, :reg),
            field(rs2.name, 24, 20, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 31, to: 31}, in_imm: {from: 31, to: 12}, replicate: true},
                        {in_insn: {from: 7, to: 7}, in_imm: {from: 11, to: 11},   replicate: false}, 
                        {in_insn: {from: 30, to: 25}, in_imm: {from: 10, to: 5},  replicate: false},
                        {in_insn: {from: 11, to: 8}, in_imm: {from: 4, to: 1},    replicate: false}
                       ],
                       shift: 1}),
            funct3_field,
            opcode_field,   
        ], lead_bits([opcode_field, funct3_field])
    end

    #----- U -----
    def format_u(name, rd) 
        opcode = {   
            lui:   0b0110111, 
            auipc: 0b0010111,
        }[name]

        opcode_field = field(:opcode, 6, 0, opcode)
        return :U, [
            field(rd.name, 11, 7, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 31, to: 20}, in_imm: {from: 31, to: 20},  replicate: false},
                        {in_insn: {from: 19, to: 12}, in_imm: {from: 19, to: 12},  replicate: false}, 
                       ],
                       shift: 12}),
            opcode_field,
        ], lead_bits([opcode_field])
    end

    #----- J -----
    def format_j(name, rd) 
        opcode_field = field(:opcode, 6, 0, 0b1101111)
        return :J, [
            field(rd.name, 11, 7, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 31, to: 31}, in_imm: {from: 31, to: 20},  replicate: true},
                        {in_insn: {from: 19, to: 12}, in_imm: {from: 19, to: 12},  replicate: false},
                        {in_insn: {from: 20, to: 20}, in_imm: {from: 11, to: 11},  replicate: false}, 
                        {in_insn: {from: 30, to: 21}, in_imm: {from: 10, to: 1},   replicate: false}, 
                       ],
                       shift: 1}),
            opcode_field,
        ], lead_bits([opcode_field])
    end

    # returns string
    # the order of the arguments fun1 and fun2 does not matter
    def lead_bits(fields, insn_bit_len= 32)
        fields.sort_by!(&:from).reverse # make right order from most to least significant
        lead_bits_str = "x" * insn_bit_len

        fields.each do |field|        
            width = (field.from - field.to + 1)
            mask = ((1 << width ) - 1) 
            str = (field.value & mask).to_s(2).rjust(width, '0')
            lead_bits_str[insn_bit_len - 1 - field.from, width] = str
            # puts "#{field.value}, #{lead_bits_str}"
        end

        return lead_bits_str
    end

    #-------------- funct3, funct7 values  ----------------
    #----- I -----
    def format_i_alu(name, rd, rs1)
        funct3 =
        {
            addi:  0,
            slti:  2,
            sltiu: 3,
            xori:  4,
            ori:   6,
            andi:  7,
        }[name]
        format_i(rs1, funct3, rd, 0b0010011)
    end

    def format_i_mem(name, rd, rs1) 
        funct3 = {
            lb:  0,
            lh:  1,
            lw:  2,
            lbu: 4,
            lhu: 5,
        }[name]
        format_i(rs1, funct3, rd, 0b0000011)
    end

    def format_i_shift(name, rd, rs1)
        pair = {
            slli:  [1, 0],
            srli:  [5, 0],
            srai:  [5, 1 << 5],
        }[name]
        funct3, funct7 = pair[0], pair[1]

        funct_3_field = field(:funct3, 14, 12, funct3)
        funct_7_field = field(:funct7, 31, 25, funct7)
        opcode_field = field(:opcode, 6, 0, 0b0010011)

        return :I, [
            field(rd.name, 11, 7, :reg),
            field(rs1.name, 19, 15, :reg),
            imm_parts({parts: [
                        {in_insn: {from: 24, to: 20}, in_imm: {from: 4, to: 0},  replicate: false}
                       ],
                       shift: 0}),
            funct_3_field,
            funct_7_field,
            opcode_field,
        ], lead_bits([funct_3_field, funct_7_field, opcode_field])
    end

    def format_i_jump(name, rd, rs1)
        funct3 = {
            jalr: 0,
        }[name]
        format_i(rs1, funct3, rd, 0b1100111)
    end

    def format_sys(name)
        case name
            when :ecall, :ebreak
                opcode_field = field(:opcode, 6, 0, 0b1110011)
                funct3_field = field(:funct3, 14, 12, 0)

                funct12 = {
                    ecall: 0,
                    ebreak: 1,
                }[name]

                funct12_field = field(:funct12, 31, 20, funct12)
                
                return :Sys, [
                    funct3_field, 
                    funct12_field,
                    opcode_field
                ], lead_bits([funct3_field, funct12_field, opcode_field])
            when :fence
                opcode_field = field(:opcode, 6, 0, 0b0001111)            
                funct3_field = field(:funct3, 14, 12, 0)
                return :Sys, [
                    funct3_field, 
                    opcode_field
                ], lead_bits([funct3_field, opcode_field])                
        end
        
    end
end
