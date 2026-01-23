#include "op.h"

void exec_add(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp0;
	_tmp0 = (rs1 + rs2);
	rd = _tmp0;
	cpu.regs[num_rd] = rd;
}

void exec_sub(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp1;
	_tmp1 = (rs1 - rs2);
	rd = _tmp1;
	cpu.regs[num_rd] = rd;
}

void exec_xor(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp2;
	_tmp2 = (rs1 ^ rs2);
	rd = _tmp2;
	cpu.regs[num_rd] = rd;
}

void exec_or(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp3;
	_tmp3 = (rs1 | rs2);
	rd = _tmp3;
	cpu.regs[num_rd] = rd;
}

void exec_and(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp4;
	_tmp4 = (rs1 & rs2);
	rd = _tmp4;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp7;
	_tmp7 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp8;
	_tmp8 = (rs1 << _tmp7);
	rd = _tmp8;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp11;
	_tmp11 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp12;
	_tmp12 = (rs1 >> _tmp11);
	rd = _tmp12;
	cpu.regs[num_rd] = rd;
}

void exec_slt(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp13;
	_tmp13 = less_signed(cpu, num_rs1, num_rs2);
	uint32_t _tmp14;
	_tmp14 = ((bool)_tmp13) ? 1 : 0;
	rd = _tmp14;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp15;
	_tmp15 = less_unsign(cpu, num_rs1, num_rs2);
	uint32_t _tmp16;
	_tmp16 = ((bool)_tmp15) ? 1 : 0;
	rd = _tmp16;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp19;
	_tmp19 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp20;
	_tmp20 = op_sra(cpu, num_rs1, _tmp19);
	rd = _tmp20;
	cpu.regs[num_rd] = rd;
}

