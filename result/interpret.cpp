#include "op.h"

void exec_add(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
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

void exec_sub(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
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

void exec_sll(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp4;
	_tmp4 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp5;
	_tmp5 = rs1 << _tmp4;
	rd = _tmp5;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp8;
	_tmp8 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp9;
	_tmp9 = rs1 >> _tmp8;
	rd = _tmp9;
	cpu.regs[num_rd] = rd;
}
