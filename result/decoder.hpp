#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include <stdexcept>
#include "op.h"

// Execution functions declarations
void exec_lb(SPU& spu, rd, rs1, imm);
void exec_lh(SPU& spu, rd, rs1, imm);
void exec_lw(SPU& spu, rd, rs1, imm);
void exec_lbu(SPU& spu, rd, rs1, imm);
void exec_lhu(SPU& spu, rd, rs1, imm);
void exec_slli(SPU& spu, rd, rs1, imm);
void exec_srli(SPU& spu, rd, rs1, imm);
void exec_srai(SPU& spu, rd, rs1, imm);
void exec_auipc(SPU& spu, rd, imm);
void exec_sb(SPU& spu, rs1, rs2, imm);
void exec_sh(SPU& spu, rs1, rs2, imm);
void exec_sw(SPU& spu, rs1, rs2, imm);
void exec_add(SPU& spu, rd, rs1, rs2);
void exec_sub(SPU& spu, rd, rs1, rs2);
void exec_mulh(SPU& spu, rd, rs1, rs2);
void exec_mulhsu(SPU& spu, rd, rs1, rs2);
void exec_mulhu(SPU& spu, rd, rs1, rs2);
void exec_div(SPU& spu, rd, rs1, rs2);
void exec_divu(SPU& spu, rd, rs1, rs2);
void exec_rem(SPU& spu, rd, rs1, rs2);
void exec_remu(SPU& spu, rd, rs1, rs2);
void exec_slt(SPU& spu, rd, rs1, rs2);
void exec_sltu(SPU& spu, rd, rs1, rs2);
void exec_xor(SPU& spu, rd, rs1, rs2);
void exec_srl(SPU& spu, rd, rs1, rs2);
void exec_sra(SPU& spu, rd, rs1, rs2);
void exec_or(SPU& spu, rd, rs1, rs2);
void exec_and(SPU& spu, rd, rs1, rs2);
void exec_lui(SPU& spu, rd, imm);
void exec_beq(SPU& spu, rs1, rs2, imm);
void exec_bne(SPU& spu, rs1, rs2, imm);
void exec_blt(SPU& spu, rs1, rs2, imm);
void exec_bge(SPU& spu, rs1, rs2, imm);
void exec_bltu(SPU& spu, rs1, rs2, imm);
void exec_bgeu(SPU& spu, rs1, rs2, imm);
void exec_jalr(SPU& spu, rd, rs1, imm);
void exec_jal(SPU& spu, rd, imm);

// Main decoder function
uint32_t decode_and_execute(SPU& spu, uint32_t insn);

#endif // DECODER_HPP