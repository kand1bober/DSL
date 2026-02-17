// Auto-generated decoder from YAML tree
#include "decode.h"

Instruction decode(SPU& spu, Register machine_word) {
	Instruction insn{};

    // Extract bits [6:0] (width: 7)
    uint32_t field_6_0 = (machine_word) & (0x7f << 0);
    switch (field_6_0) {
        case 0x3: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (machine_word) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                        insn.insn_type = LB;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x1000: {
                        insn.insn_type = LH;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x2000: {
                        insn.insn_type = LW;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x4000: {
                        insn.insn_type = LBU;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x5000: {
                        insn.insn_type = LHU;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
            }
        }
        case 0x13: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (machine_word) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                        insn.insn_type = ADDI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x1000: {
                        insn.insn_type = SLLI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (0) | (((machine_word >> 20) & (1 << 5) - 1) << 0)
                        };
                    return insn;
                }
                case 0x2000: {
                        insn.insn_type = SLTI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x3000: {
                        insn.insn_type = SLTIU;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x4000: {
                        insn.insn_type = XORI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = SRLI;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (0) | (((machine_word >> 20) & (1 << 5) - 1) << 0)
                                };
                            return insn;
                        }
                        case 0x40000000: {
                                insn.insn_type = SRAI;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (0) | (((machine_word >> 20) & (1 << 5) - 1) << 0)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x6000: {
                        insn.insn_type = ORI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                case 0x7000: {
                        insn.insn_type = ANDI;
                        insn.oprnds = {
                            (machine_word >> 7) & ((1 << 5) - 1),
                            (machine_word >> 15) & ((1 << 5) - 1),
                            ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                        };
                    return insn;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
            }
        }
        case 0x17: {
                insn.insn_type = AUIPC;
                insn.oprnds = {
                    (machine_word >> 7) & ((1 << 5) - 1),
                    ((0) | (((machine_word >> 20) & (1 << 12) - 1) << 20)) | (((machine_word >> 12) & (1 << 8) - 1) << 12)
                };
            return insn;
        }
        case 0x23: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (machine_word) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                        insn.insn_type = SB;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)) | (((machine_word >> 7) & (1 << 1) - 1) << 0)
                        };
                    return insn;
                }
                case 0x1000: {
                        insn.insn_type = SH;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)) | (((machine_word >> 7) & (1 << 1) - 1) << 0)
                        };
                    return insn;
                }
                case 0x2000: {
                        insn.insn_type = SW;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)) | (((machine_word >> 7) & (1 << 1) - 1) << 0)
                        };
                    return insn;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
            }
        }
        case 0x33: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (machine_word) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = ADD;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = MUL;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x40000000: {
                                insn.insn_type = SUB;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x1000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = SLL;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = MULH;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x2000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = SLT;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = MULHSU;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x3000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = SLTU;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = MULHU;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x4000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = XOR;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = DIV;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = SRL;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = DIVU;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x40000000: {
                                insn.insn_type = SRA;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x6000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = OR;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = REM;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                case 0x7000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (machine_word) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                                insn.insn_type = AND;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        case 0x2000000: {
                                insn.insn_type = REMU;
                                insn.oprnds = {
                                    (machine_word >> 7) & ((1 << 5) - 1),
                                    (machine_word >> 15) & ((1 << 5) - 1),
                                    (machine_word >> 20) & ((1 << 5) - 1)
                                };
                            return insn;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
                    }
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
            }
        }
        case 0x37: {
                insn.insn_type = LUI;
                insn.oprnds = {
                    (machine_word >> 7) & ((1 << 5) - 1),
                    ((0) | (((machine_word >> 20) & (1 << 12) - 1) << 20)) | (((machine_word >> 12) & (1 << 8) - 1) << 12)
                };
            return insn;
        }
        case 0x63: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (machine_word) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                        insn.insn_type = BEQ;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                case 0x1000: {
                        insn.insn_type = BNE;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                case 0x4000: {
                        insn.insn_type = BLT;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                case 0x5000: {
                        insn.insn_type = BGE;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                case 0x6000: {
                        insn.insn_type = BLTU;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                case 0x7000: {
                        insn.insn_type = BGEU;
                        insn.oprnds = {
                            (machine_word >> 15) & ((1 << 5) - 1),
                            (machine_word >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((machine_word >> 7) & (1 << 1) - 1) << 11)) | (((machine_word >> 25) & (1 << 6) - 1) << 5)) | (((machine_word >> 8) & (1 << 4) - 1) << 1)
                        };
                    return insn;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
            }
        }
        case 0x67: {
                insn.insn_type = JALR;
                insn.oprnds = {
                    (machine_word >> 7) & ((1 << 5) - 1),
                    (machine_word >> 15) & ((1 << 5) - 1),
                    ((0) | ((((machine_word >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((machine_word >> 20) & (1 << 11) - 1) << 0)
                };
            return insn;
        }
        case 0x6f: {
                insn.insn_type = JAL;
                insn.oprnds = {
                    (machine_word >> 7) & ((1 << 5) - 1),
                    ((((0) | ((((machine_word >> 31) & 1) ? ((1 << 12) - 1) : 0) << 20)) | (((machine_word >> 12) & (1 << 8) - 1) << 12)) | (((machine_word >> 20) & (1 << 1) - 1) << 11)) | (((machine_word >> 21) & (1 << 10) - 1) << 1)
                };
            return insn;
        }
        case 0x73: {
                insn.insn_type = ECALL;
                insn.oprnds = {

                };
            return insn;
        }
        default:
            throw std::runtime_error("Unknown insn: 0x" + std::to_string(machine_word));
    }
}