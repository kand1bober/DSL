#include <cstdint>
#include <array>
#include <stdbool.h>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "decoder.h"

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

typedef uint32_t Register;
typedef int32_t  SignedRegister;

struct CPU { 
    std::array<Register, 32> regs; 
    Register pc;
};

struct Ram {
    std::array<uint8_t, 4096> data;
};

class SPU {
public:
    CPU cpu;
    Ram mem;

    void run(const std::vector<Register>& program) {
        cpu.pc = 0;

        while (cpu.pc < program.size()) {
            //fetch
            uint32_t insn = program[cpu.pc];

            //decode
            std::cout << "decoding: " << std::hex << insn << std::endl;
            DecodedOperation operation = decode(*this, insn);

            //execute
            operation(*this);

            //update pc 
            cpu.pc += 1;
        }
    }
};

Register bit_extract(SPU& spu, Register src, Register from, Register to);

bool less_signed(SPU& spu, Register a, Register b);
bool more_equal_signed(SPU& spu, Register a, Register b);
bool less_unsign(SPU& spu, Register a, Register b);
bool more_equal_unsign(SPU& spu, Register a, Register b);

Register div_signed(SPU& spu, Register a, Register b);
Register div_unsign(SPU& spu, Register a, Register b);
Register rem_signed(SPU& spu, Register a, Register b);
Register rem_unsign(SPU& spu, Register a, Register b);

Register op_sra(SPU& spu, Register a, Register b);

Register sign_extend(SPU& spu, Register a, Register b);
Register zero_extend(SPU& spu, Register a, Register b);

Register readMem8(SPU& spu, uint32_t addr);
Register readMem16(SPU& spu, uint32_t addr);
Register readMem32(SPU& spu, uint32_t addr);

Register writeMem8(SPU& spu, uint32_t addr, Register val);
Register writeMem16(SPU& spu, uint32_t addr, Register val);
Register writeMem32(SPU& spu, uint32_t addr, Register val);

// Begin of auto-generated prototypes
	// Execution functions declarations
	void exec_add(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sub(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_xor(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_or(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_and(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_slt(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sltu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sll(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_srl(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sra(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mul(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulh(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulhsu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulhu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_div(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_divu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_rem(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_remu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_addi(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_xori(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_ori(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_andi(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_slti(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_sltiu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_slli(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_srli(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_srai(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_jalr(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lb(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lh(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lw(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lbu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lhu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_sb(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_sh(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_sw(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_beq(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bne(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_blt(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bge(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bltu(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bgeu(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_lui(SPU& spu, Register rd, Register imm);
	void exec_auipc(SPU& spu, Register rd, Register imm);
	void exec_jal(SPU& spu, Register rd, Register imm);

// End of auto-generated prototypes

#endif
