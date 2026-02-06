// Auto-generated decoder from YAML tree
#include "decoder.hpp"

// Main decoder implementation
uint32_t decode_and_execute(SPU& spu, uint32_t insn) {
    // Start decoding from the root
    // Extract bits [6:0] (width: 7)
    uint32_t field_6_0 = (insn) & (0x7f << 0);
    switch (field_6_0) {
        case 0x3: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_lb(spu, );
                    break;
                }
                case 0x1000: {
                    exec_lh(spu, );
                    break;
                }
                case 0x2000: {
                    exec_lw(spu, );
                    break;
                }
                case 0x4000: {
                    exec_lbu(spu, );
                    break;
                }
                case 0x5000: {
                    exec_lhu(spu, );
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x13: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x1000: {
                    exec_slli(spu, );
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srli(spu, );
                            break;
                        }
                        case 0x40000000: {
                            exec_srai(spu, );
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x17: {
            exec_auipc(spu, );
            break;
        }
        case 0x23: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_sb(spu, );
                    break;
                }
                case 0x1000: {
                    exec_sh(spu, );
                    break;
                }
                case 0x2000: {
                    exec_sw(spu, );
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x33: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_add(spu, );
                            break;
                        }
                        case 0x40000000: {
                            exec_sub(spu, );
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x1000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x2000000: {
                            exec_mulh(spu, );
                            break;
                        }
                        case 0x4000000: {
                            exec_mulhsu(spu, );
                            break;
                        }
                        case 0x6000000: {
                            exec_mulhu(spu, );
                            break;
                        }
                        case 0x8000000: {
                            exec_div(spu, );
                            break;
                        }
                        case 0xa000000: {
                            exec_divu(spu, );
                            break;
                        }
                        case 0xc000000: {
                            exec_rem(spu, );
                            break;
                        }
                        case 0xe000000: {
                            exec_remu(spu, );
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x2000: {
                    exec_slt(spu, );
                    break;
                }
                case 0x3000: {
                    exec_sltu(spu, );
                    break;
                }
                case 0x4000: {
                    exec_xor(spu, );
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srl(spu, );
                            break;
                        }
                        case 0x40000000: {
                            exec_sra(spu, );
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x6000: {
                    exec_or(spu, );
                    break;
                }
                case 0x7000: {
                    exec_and(spu, );
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x37: {
            exec_lui(spu, );
            break;
        }
        case 0x63: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_beq(spu, );
                    break;
                }
                case 0x1000: {
                    exec_bne(spu, );
                    break;
                }
                case 0x4000: {
                    exec_blt(spu, );
                    break;
                }
                case 0x5000: {
                    exec_bge(spu, );
                    break;
                }
                case 0x6000: {
                    exec_bltu(spu, );
                    break;
                }
                case 0x7000: {
                    exec_bgeu(spu, );
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x67: {
            exec_jalr(spu, );
            break;
        }
        case 0x6f: {
            exec_jal(spu, );
            break;
        }
        default:
            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
    }
    return 0;
}