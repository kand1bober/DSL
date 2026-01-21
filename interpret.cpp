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

void exec_sll(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp5;
	uint32_t _tmp5 = rs1 << rs2;
	cpu.regs[rd] = rd;
}

void exec_slt(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp6;
	uint32_t _tmp6 = rs1 < rs2;
	cpu.regs[rd] = rd;
}

void exec_sltu(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp7;
	uint32_t _tmp7 = rs1 < rs2;
	cpu.regs[rd] = rd;
}

void exec_srl(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp8;
	uint32_t _tmp8 = rs1 >> rs2;
	cpu.regs[rd] = rd;
}

void exec_sra(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp9;
	uint32_t _tmp9 = rs1 >>> rs2;
	cpu.regs[rd] = rd;
}

void exec_mul(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp10;
	uint32_t _tmp10 = rs1 * rs2;
	cpu.regs[rd] = rd;
}

void exec_mulh(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp11;
	uint32_t _tmp11 = rs1 * rs2;
	cpu.regs[rd] = rd;
}

void exec_mulhsu(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp12;
	uint32_t _tmp12 = rs1 * rs2;
	cpu.regs[rd] = rd;
}

void exec_mulhu(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp13;
	uint32_t _tmp13 = rs1 * rs2;
	cpu.regs[rd] = rd;
}

void exec_div(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp14;
	uint32_t _tmp14 = rs1 / rs2;
	cpu.regs[rd] = rd;
}

void exec_divu(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp15;
	uint32_t _tmp15 = rs1 / rs2;
	cpu.regs[rd] = rd;
}

void exec_rem(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp16;
	uint32_t _tmp16 = rs1 % rs2;
	cpu.regs[rd] = rd;
}

void exec_remu(CPU &cpu) {
	uint32_t rd;
	uint32_t rs1;
	uint32_t rs1 = cpu.regs[rs1];
	uint32_t rs2;
	uint32_t rs2 = cpu.regs[rs2];
	uint32_t _tmp17;
	uint32_t _tmp17 = rs1 % rs2;
	cpu.regs[rd] = rd;
}

