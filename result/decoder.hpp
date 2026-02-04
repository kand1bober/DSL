#ifndef DECODER_HPP
#define DECODER_HPP

#include <cstdint>
#include <stdexcept>
#include "op.h"

// Execution functions declarations
void exec_lb(uint32_t insn, SPU& spu);
void exec_lh(uint32_t insn, SPU& spu);
void exec_lw(uint32_t insn, SPU& spu);
void exec_lbu(uint32_t insn, SPU& spu);
void exec_lhu(uint32_t insn, SPU& spu);
void exec_slli(uint32_t insn, SPU& spu);
void exec_srli(uint32_t insn, SPU& spu);
void exec_srai(uint32_t insn, SPU& spu);
void exec_auipc(uint32_t insn, SPU& spu);
void exec_sb(uint32_t insn, SPU& spu);
void exec_sh(uint32_t insn, SPU& spu);
void exec_sw(uint32_t insn, SPU& spu);
void exec_add(uint32_t insn, SPU& spu);
void exec_sub(uint32_t insn, SPU& spu);
void exec_mulh(uint32_t insn, SPU& spu);
void exec_mulhsu(uint32_t insn, SPU& spu);
void exec_mulhu(uint32_t insn, SPU& spu);
void exec_div(uint32_t insn, SPU& spu);
void exec_divu(uint32_t insn, SPU& spu);
void exec_rem(uint32_t insn, SPU& spu);
void exec_remu(uint32_t insn, SPU& spu);
void exec_slt(uint32_t insn, SPU& spu);
void exec_sltu(uint32_t insn, SPU& spu);
void exec_xor(uint32_t insn, SPU& spu);
void exec_srl(uint32_t insn, SPU& spu);
void exec_sra(uint32_t insn, SPU& spu);
void exec_or(uint32_t insn, SPU& spu);
void exec_and(uint32_t insn, SPU& spu);
void exec_lui(uint32_t insn, SPU& spu);
void exec_beq(uint32_t insn, SPU& spu);
void exec_bne(uint32_t insn, SPU& spu);
void exec_blt(uint32_t insn, SPU& spu);
void exec_bge(uint32_t insn, SPU& spu);
void exec_bltu(uint32_t insn, SPU& spu);
void exec_bgeu(uint32_t insn, SPU& spu);
void exec_jalr(uint32_t insn, SPU& spu);
void exec_jal(uint32_t insn, SPU& spu);

// Main decoder function
uint32_t decode_and_execute(uint32_t insn, SPU& spu);

#endif // DECODER_HPP