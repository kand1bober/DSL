#ifndef DECODER_HEADER
#define DECODER_HEADER

#include <cstdint>
#include <stdexcept>
#include <string>

class SPU;
typedef uint32_t Register;

struct DecodedOperands {
	Register a;
	Register b;
	Register c;
};

enum InsnType {
	LB,
	LH,
	LW,
	LBU,
	LHU,
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
	SUB,
	MULH,
	MULHSU,
	MULHU,
	DIV,
	DIVU,
	REM,
	REMU,
	SLT,
	SLTU,
	XOR,
	SRL,
	SRA,
	OR,
	AND,
	LUI,
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,
	JALR,
	JAL,
};

struct Instruction {
	InsnType insn_type;
	DecodedOperands oprnds;
};

Instruction decode(SPU& spu, Register machine_word);

#endif