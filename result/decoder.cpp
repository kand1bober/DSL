// Auto-generated decoder from YAML tree
#include "decoder.hpp"

// Main decoder implementation
uint32_t decode_and_execute(uint32_t insn, SPU& spu) {
    // Start decoding from the root
    // Extract bits [6:0] (width: 7)
    uint32_t field_6_0 = (insn) & (0x7f << 0);
    switch (field_6_0) {
        case 0x3: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_lb(insn, spu);
                    break;
                }
                case 0x1000: {
                    exec_lh(insn, spu);
                    break;
                }
                case 0x2000: {
                    exec_lw(insn, spu);
                    break;
                }
                case 0x4000: {
                    exec_lbu(insn, spu);
                    break;
                }
                case 0x5000: {
                    exec_lhu(insn, spu);
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
                    exec_slli(insn, spu);
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srli(insn, spu);
                            break;
                        }
                        case 0x40000000: {
                            exec_srai(insn, spu);
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
            exec_auipc(insn, spu);
            break;
        }
        case 0x23: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_sb(insn, spu);
                    break;
                }
                case 0x1000: {
                    exec_sh(insn, spu);
                    break;
                }
                case 0x2000: {
                    exec_sw(insn, spu);
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
                            exec_add(insn, spu);
                            break;
                        }
                        case 0x40000000: {
                            exec_sub(insn, spu);
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
                            exec_mulh(insn, spu);
                            break;
                        }
                        case 0x4000000: {
                            exec_mulhsu(insn, spu);
                            break;
                        }
                        case 0x6000000: {
                            exec_mulhu(insn, spu);
                            break;
                        }
                        case 0x8000000: {
                            exec_div(insn, spu);
                            break;
                        }
                        case 0xa000000: {
                            exec_divu(insn, spu);
                            break;
                        }
                        case 0xc000000: {
                            exec_rem(insn, spu);
                            break;
                        }
                        case 0xe000000: {
                            exec_remu(insn, spu);
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x2000: {
                    exec_slt(insn, spu);
                    break;
                }
                case 0x3000: {
                    exec_sltu(insn, spu);
                    break;
                }
                case 0x4000: {
                    exec_xor(insn, spu);
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srl(insn, spu);
                            break;
                        }
                        case 0x40000000: {
                            exec_sra(insn, spu);
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x6000: {
                    exec_or(insn, spu);
                    break;
                }
                case 0x7000: {
                    exec_and(insn, spu);
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x37: {
            exec_lui(insn, spu);
            break;
        }
        case 0x63: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_beq(insn, spu);
                    break;
                }
                case 0x1000: {
                    exec_bne(insn, spu);
                    break;
                }
                case 0x4000: {
                    exec_blt(insn, spu);
                    break;
                }
                case 0x5000: {
                    exec_bge(insn, spu);
                    break;
                }
                case 0x6000: {
                    exec_bltu(insn, spu);
                    break;
                }
                case 0x7000: {
                    exec_bgeu(insn, spu);
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x67: {
            exec_jalr(insn, spu);
            break;
        }
        case 0x6f: {
            exec_jal(insn, spu);
            break;
        }
        default:
            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
    }
    return 0;
}