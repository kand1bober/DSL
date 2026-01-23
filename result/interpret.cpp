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

void exec_slt(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp5;
	_tmp5 = less_signed(cpu, num_rs1, num_rs2);
	uint32_t _tmp6;
	_tmp6 = ((bool)_tmp5) ? 1 : 0;
	rd = _tmp6;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp7;
	_tmp7 = less_unsign(cpu, num_rs1, num_rs2);
	uint32_t _tmp8;
	_tmp8 = ((bool)_tmp7) ? 1 : 0;
	rd = _tmp8;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp11;
	_tmp11 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp12;
	_tmp12 = (rs1 << _tmp11);
	rd = _tmp12;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp15;
	_tmp15 = bit_extract(cpu, num_rs2, 4, 0);
	uint32_t _tmp16;
	_tmp16 = (rs1 >> _tmp15);
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

void exec_mul(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp21;
	int32_t _tmp21 = (int32_t)(rs1);
	uint32_t _tmp22;
	int32_t _tmp22 = (int32_t)(rs2);
	uint32_t _tmp23;
	_tmp23 = (_tmp21 * _tmp22);
	uint32_t _tmp26;
	_tmp26 = bit_extract(cpu, _tmp23, 31, 0);
	rd = _tmp26;
	cpu.regs[num_rd] = rd;
}

void exec_mulh(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp27;
	int32_t _tmp27 = (int32_t)(rs1);
	uint32_t _tmp28;
	int32_t _tmp28 = (int32_t)(rs2);
	uint32_t _tmp29;
	_tmp29 = (_tmp27 * _tmp28);
	uint32_t _tmp32;
	_tmp32 = bit_extract(cpu, _tmp29, 63, 32);
	rd = _tmp32;
	cpu.regs[num_rd] = rd;
}

void exec_mulhsu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp33;
	int32_t _tmp33 = (int32_t)(rs1);
	uint32_t _tmp34;
	uint32_t _tmp34 = (uint32_t)(rs2);
	uint32_t _tmp35;
	_tmp35 = (_tmp33 * _tmp34);
	uint32_t _tmp38;
	_tmp38 = bit_extract(cpu, _tmp35, 63, 32);
	rd = _tmp38;
	cpu.regs[num_rd] = rd;
}

void exec_mulhu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp39;
	uint32_t _tmp39 = (uint32_t)(rs1);
	uint32_t _tmp40;
	uint32_t _tmp40 = (uint32_t)(rs2);
	uint32_t _tmp41;
	_tmp41 = (_tmp39 * _tmp40);
	uint32_t _tmp44;
	_tmp44 = bit_extract(cpu, _tmp41, 63, 32);
	rd = _tmp44;
	cpu.regs[num_rd] = rd;
}

void exec_div(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp45;
	_tmp45 = div_signed(cpu, num_rs1, num_rs2);
	rd = _tmp45;
	cpu.regs[num_rd] = rd;
}

void exec_divu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp46;
	_tmp46 = div_unsign(cpu, num_rs1, num_rs2);
	rd = _tmp46;
	cpu.regs[num_rd] = rd;
}

void exec_rem(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp47;
	_tmp47 = rem_signed(cpu, num_rs1, num_rs2);
	rd = _tmp47;
	cpu.regs[num_rd] = rd;
}

void exec_remu(CPU &cpu, uint32_t num_rd, uint32_t num_rs1, uint32_t num_rs2) {
	uint32_t rd;
	uint32_t rs1;
	rs1 = cpu.regs[num_rs1];
	uint32_t rs2;
	rs2 = cpu.regs[num_rs2];
	uint32_t _tmp48;
	_tmp48 = rem_unsign(cpu, num_rs1, num_rs2);
	rd = _tmp48;
	cpu.regs[num_rd] = rd;
}

