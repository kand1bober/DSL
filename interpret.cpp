#include <cstdint>
#include <array>
struct CPU { std::array<uint32_t,32> regs; };

void exec_add(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp0;
	_tmp0 = rs1 + rs2;
	rd = _tmp0;
	cpu.regs[num_rd] = rd;
}

void exec_sub(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp1;
	_tmp1 = rs1 - rs2;
	rd = _tmp1;
	cpu.regs[num_rd] = rd;
}

void exec_or(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp2;
	_tmp2 = rs1 | rs2;
	rd = _tmp2;
	cpu.regs[num_rd] = rd;
}

void exec_and(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp3;
	_tmp3 = rs1 & rs2;
	rd = _tmp3;
	cpu.regs[num_rd] = rd;
}

void exec_xor(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp4;
	_tmp4 = rs1 ^ rs2;
	rd = _tmp4;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp5;
	_tmp5 = rs1 << rs2;
	rd = _tmp5;
	cpu.regs[num_rd] = rd;
}

void exec_slt(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp6;
	_tmp6 = rs1 < rs2;
	rd = _tmp6;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp7;
	_tmp7 = rs1 < rs2;
	rd = _tmp7;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp8;
	_tmp8 = rs1 >> rs2;
	rd = _tmp8;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp9;
	_tmp9 = rs1 >>> rs2;
	rd = _tmp9;
	cpu.regs[num_rd] = rd;
}

void exec_mul(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp10;
	_tmp10 = rs1 * rs2;
	rd = _tmp10;
	cpu.regs[num_rd] = rd;
}

void exec_mulh(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp11;
	_tmp11 = rs1 * rs2;
	rd = _tmp11;
	cpu.regs[num_rd] = rd;
}

void exec_mulhsu(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp12;
	_tmp12 = rs1 * rs2;
	rd = _tmp12;
	cpu.regs[num_rd] = rd;
}

void exec_mulhu(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp13;
	_tmp13 = rs1 * rs2;
	rd = _tmp13;
	cpu.regs[num_rd] = rd;
}

void exec_div(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp14;
	_tmp14 = rs1 / rs2;
	rd = _tmp14;
	cpu.regs[num_rd] = rd;
}

void exec_divu(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp15;
	_tmp15 = rs1 / rs2;
	rd = _tmp15;
	cpu.regs[num_rd] = rd;
}

void exec_rem(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp16;
	_tmp16 = rs1 % rs2;
	rd = _tmp16;
	cpu.regs[num_rd] = rd;
}

void exec_remu(CPU &cpu, num_rd, num_rs1, num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp17;
	_tmp17 = rs1 % rs2;
	rd = _tmp17;
	cpu.regs[num_rd] = rd;
}

