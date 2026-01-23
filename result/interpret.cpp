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

void exec_slt(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp2;
	_tmp2 = less_signed(cpu, num_rs1, num_rs2);
	uint32_t _tmp3;
	_tmp3 = ((bool)_tmp2) ? 1 : 0;
	rd = _tmp3;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp4;
	_tmp4 = less_unsign(cpu, num_rs1, num_rs2);
	uint32_t _tmp5;
	_tmp5 = ((bool)_tmp4) ? 1 : 0;
	rd = _tmp5;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp8;
	_tmp8 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp9;
	_tmp9 = (rs1 << _tmp8);
	rd = _tmp9;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp12;
	_tmp12 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp13;
	_tmp13 = (rs1 >> _tmp12);
	rd = _tmp13;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp16;
	_tmp16 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp17;
	_tmp17 = op_sra(cpu, num_rs1, _tmp16);
	rd = _tmp17;
	cpu.regs[num_rd] = rd;
}

