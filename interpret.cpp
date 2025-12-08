#include <cstdint>
#include <array>
struct CPU { std::array<uint32_t,32> regs; };

void exec_add(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp0;
	uint32_t _tmp0 = rs1 + rs2;
	cpu.regs[rd] = rd;
}

void exec_sub(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp1;
	uint32_t _tmp1 = rs1 - rs2;
	cpu.regs[rd] = rd;
}

void exec_or(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp2;
	uint32_t _tmp2 = rs1 | rs2;
	cpu.regs[rd] = rd;
}

void exec_and(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp3;
	uint32_t _tmp3 = rs1 & rs2;
	cpu.regs[rd] = rd;
}

void exec_xor(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp4;
	uint32_t _tmp4 = rs1 ^ rs2;
	cpu.regs[rd] = rd;
}

