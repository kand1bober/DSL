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
                    exec_lb(spu,
                            (insn >> 7) & ((1 << 5) - 1),
                            (insn >> 15) & ((1 << 5) - 1),
                            ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
                    break;
                }
                case 0x1000: {
                    exec_lh(spu,
                            (insn >> 7) & ((1 << 5) - 1),
                            (insn >> 15) & ((1 << 5) - 1),
                            ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
                    break;
                }
                case 0x2000: {
                    exec_lw(spu,
                            (insn >> 7) & ((1 << 5) - 1),
                            (insn >> 15) & ((1 << 5) - 1),
                            ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
                    break;
                }
                case 0x4000: {
                    exec_lbu(spu,
                             (insn >> 7) & ((1 << 5) - 1),
                             (insn >> 15) & ((1 << 5) - 1),
                             ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
                    break;
                }
                case 0x5000: {
                    exec_lhu(spu,
                             (insn >> 7) & ((1 << 5) - 1),
                             (insn >> 15) & ((1 << 5) - 1),
                             ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
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
                    exec_slli(spu,
                              (insn >> 7) & ((1 << 5) - 1),
                              (insn >> 15) & ((1 << 5) - 1),
                              (0) | (((insn >> 20) & (1 << 5) - 1) << 0));
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srli(spu,
                                      (insn >> 7) & ((1 << 5) - 1),
                                      (insn >> 15) & ((1 << 5) - 1),
                                      (0) | (((insn >> 20) & (1 << 5) - 1) << 0));
                            break;
                        }
                        case 0x40000000: {
                            exec_srai(spu,
                                      (insn >> 7) & ((1 << 5) - 1),
                                      (insn >> 15) & ((1 << 5) - 1),
                                      (0) | (((insn >> 20) & (1 << 5) - 1) << 0));
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
            exec_auipc(spu,
                       (insn >> 7) & ((1 << 5) - 1),
                       ((0) | (((insn >> 20) & (1 << 12) - 1) << 20)) | (((insn >> 12) & (1 << 8) - 1) << 12));
            break;
        }
        case 0x23: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_sb(spu,
                            (insn >> 15) & ((1 << 5) - 1),
                            (insn >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1)) | (((insn >> 7) & (1 << 1) - 1) << 0));
                    break;
                }
                case 0x1000: {
                    exec_sh(spu,
                            (insn >> 15) & ((1 << 5) - 1),
                            (insn >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1)) | (((insn >> 7) & (1 << 1) - 1) << 0));
                    break;
                }
                case 0x2000: {
                    exec_sw(spu,
                            (insn >> 15) & ((1 << 5) - 1),
                            (insn >> 20) & ((1 << 5) - 1),
                            ((((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1)) | (((insn >> 7) & (1 << 1) - 1) << 0));
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
                            exec_add(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0x40000000: {
                            exec_sub(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
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
                            exec_mulh(spu,
                                      (insn >> 7) & ((1 << 5) - 1),
                                      (insn >> 15) & ((1 << 5) - 1),
                                      (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0x4000000: {
                            exec_mulhsu(spu,
                                        (insn >> 7) & ((1 << 5) - 1),
                                        (insn >> 15) & ((1 << 5) - 1),
                                        (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0x6000000: {
                            exec_mulhu(spu,
                                       (insn >> 7) & ((1 << 5) - 1),
                                       (insn >> 15) & ((1 << 5) - 1),
                                       (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0x8000000: {
                            exec_div(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0xa000000: {
                            exec_divu(spu,
                                      (insn >> 7) & ((1 << 5) - 1),
                                      (insn >> 15) & ((1 << 5) - 1),
                                      (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0xc000000: {
                            exec_rem(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0xe000000: {
                            exec_remu(spu,
                                      (insn >> 7) & ((1 << 5) - 1),
                                      (insn >> 15) & ((1 << 5) - 1),
                                      (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x2000: {
                    exec_slt(spu,
                             (insn >> 7) & ((1 << 5) - 1),
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1));
                    break;
                }
                case 0x3000: {
                    exec_sltu(spu,
                              (insn >> 7) & ((1 << 5) - 1),
                              (insn >> 15) & ((1 << 5) - 1),
                              (insn >> 20) & ((1 << 5) - 1));
                    break;
                }
                case 0x4000: {
                    exec_xor(spu,
                             (insn >> 7) & ((1 << 5) - 1),
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1));
                    break;
                }
                case 0x5000: {
                    // Extract bits [31:25] (width: 7)
                    uint32_t field_31_25 = (insn) & (0x7f << 25);
                    switch (field_31_25) {
                        case 0x0: {
                            exec_srl(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        case 0x40000000: {
                            exec_sra(spu,
                                     (insn >> 7) & ((1 << 5) - 1),
                                     (insn >> 15) & ((1 << 5) - 1),
                                     (insn >> 20) & ((1 << 5) - 1));
                            break;
                        }
                        default:
                            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
                    }
                    break;
                }
                case 0x6000: {
                    exec_or(spu,
                            (insn >> 7) & ((1 << 5) - 1),
                            (insn >> 15) & ((1 << 5) - 1),
                            (insn >> 20) & ((1 << 5) - 1));
                    break;
                }
                case 0x7000: {
                    exec_and(spu,
                             (insn >> 7) & ((1 << 5) - 1),
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1));
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x37: {
            exec_lui(spu,
                     (insn >> 7) & ((1 << 5) - 1),
                     ((0) | (((insn >> 20) & (1 << 12) - 1) << 20)) | (((insn >> 12) & (1 << 8) - 1) << 12));
            break;
        }
        case 0x63: {
            // Extract bits [14:12] (width: 3)
            uint32_t field_14_12 = (insn) & (0x7 << 12);
            switch (field_14_12) {
                case 0x0: {
                    exec_beq(spu,
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1),
                             ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                case 0x1000: {
                    exec_bne(spu,
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1),
                             ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                case 0x4000: {
                    exec_blt(spu,
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1),
                             ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                case 0x5000: {
                    exec_bge(spu,
                             (insn >> 15) & ((1 << 5) - 1),
                             (insn >> 20) & ((1 << 5) - 1),
                             ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                case 0x6000: {
                    exec_bltu(spu,
                              (insn >> 15) & ((1 << 5) - 1),
                              (insn >> 20) & ((1 << 5) - 1),
                              ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                case 0x7000: {
                    exec_bgeu(spu,
                              (insn >> 15) & ((1 << 5) - 1),
                              (insn >> 20) & ((1 << 5) - 1),
                              ((((0) | ((((insn >> 31) & 1) ? ((1 << 20) - 1) : 0) << 12)) | (((insn >> 7) & (1 << 1) - 1) << 11)) | (((insn >> 25) & (1 << 6) - 1) << 5)) | (((insn >> 8) & (1 << 4) - 1) << 1));
                    break;
                }
                default:
                    throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
            }
            break;
        }
        case 0x67: {
            exec_jalr(spu,
                      (insn >> 7) & ((1 << 5) - 1),
                      (insn >> 15) & ((1 << 5) - 1),
                      ((0) | ((((insn >> 31) & 1) ? ((1 << 21) - 1) : 0) << 11)) | (((insn >> 20) & (1 << 11) - 1) << 0));
            break;
        }
        case 0x6f: {
            exec_jal(spu,
                     (insn >> 7) & ((1 << 5) - 1),
                     ((((0) | ((((insn >> 31) & 1) ? ((1 << 12) - 1) : 0) << 20)) | (((insn >> 12) & (1 << 8) - 1) << 12)) | (((insn >> 20) & (1 << 1) - 1) << 11)) | (((insn >> 21) & (1 << 10) - 1) << 1));
            break;
        }
        default:
            throw std::runtime_error("Unknown insn: 0x" + std::to_string(insn));
    }
    return 0;
}