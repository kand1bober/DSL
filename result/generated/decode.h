#ifndef DECODER_HEADER
#define DECODER_HEADER

#include <cstdint>
#include <stdexcept>
#include <string>

class SPU;
typedef uint32_t Register;

struct DecodedOperands {
	Register arg1;
	Register arg2;
	Register arg3;
};

enum InsnType {
	LB,
	LH,
	LW,
	LBU,
	LHU,
	FENCE,
	ADDI,
	SLLI,
	SLTI,
	SLTIU,
	XORI,
	SRLI,
	SRAI,
	ORI,
	ANDI,
	AUIPC,
	SB,
	SH,
	SW,
	ADD,
	MUL,
	SUB,
	SLL,
	MULH,
	SLT,
	MULHSU,
	SLTU,
	MULHU,
	XOR,
	DIV,
	SRL,
	DIVU,
	SRA,
	OR,
	REM,
	AND,
	REMU,
	LUI,
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,
	JALR,
	JAL,
	ECALL,
};

struct Instruction {
	InsnType insn_type;
	DecodedOperands oprnds;
};

Instruction decode(SPU& spu, Register machine_word);

#endif