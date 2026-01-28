#include "op.h"

void exec_add(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp0;
	_tmp0 = (rs1 + rs2);
	rd = _tmp0;
	cpu.regs[num_rd] = rd;
}

void exec_sub(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp1;
	_tmp1 = (rs1 - rs2);
	rd = _tmp1;
	cpu.regs[num_rd] = rd;
}

void exec_xor(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp2;
	_tmp2 = (rs1 ^ rs2);
	rd = _tmp2;
	cpu.regs[num_rd] = rd;
}

void exec_or(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp3;
	_tmp3 = (rs1 | rs2);
	rd = _tmp3;
	cpu.regs[num_rd] = rd;
}

void exec_and(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp4;
	_tmp4 = (rs1 & rs2);
	rd = _tmp4;
	cpu.regs[num_rd] = rd;
}

void exec_slt(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp5;
	_tmp5 = less_signed(cpu, rs1, rs2);
	rd = ternary;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp6;
	_tmp6 = less_unsign(cpu, rs1, rs2);
	rd = ternary;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp9;
	_tmp9 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp10;
	_tmp10 = (rs1 << _tmp9);
	rd = _tmp10;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp13;
	_tmp13 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp14;
	_tmp14 = (rs1 >> _tmp13);
	rd = _tmp14;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp17;
	_tmp17 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp18;
	_tmp18 = op_sra(cpu, rs1, _tmp17);
	rd = _tmp18;
	cpu.regs[num_rd] = rd;
}

void exec_mul(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp19;
	_tmp19 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp22;
	_tmp22 = bit_extract(cpu, _tmp19, 31, 0);
	rd = _tmp22;
	cpu.regs[num_rd] = rd;
}

void exec_mulh(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp23;
	_tmp23 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp26;
	_tmp26 = bit_extract(cpu, _tmp23, 63, 32);
	rd = _tmp26;
	cpu.regs[num_rd] = rd;
}

void exec_mulhsu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp27;
	_tmp27 = ((SignedRegister)(rs1) * (Register)(rs2));
	Register _tmp30;
	_tmp30 = bit_extract(cpu, _tmp27, 63, 32);
	rd = _tmp30;
	cpu.regs[num_rd] = rd;
}

void exec_mulhu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp31;
	_tmp31 = ((Register)(rs1) * (Register)(rs2));
	Register _tmp34;
	_tmp34 = bit_extract(cpu, _tmp31, 63, 32);
	rd = _tmp34;
	cpu.regs[num_rd] = rd;
}

void exec_div(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp35;
	_tmp35 = div_signed(cpu, rs1, rs2);
	rd = _tmp35;
	cpu.regs[num_rd] = rd;
}

void exec_divu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp36;
	_tmp36 = div_unsign(cpu, rs1, rs2);
	rd = _tmp36;
	cpu.regs[num_rd] = rd;
}

void exec_rem(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp37;
	_tmp37 = rem_signed(cpu, rs1, rs2);
	rd = _tmp37;
	cpu.regs[num_rd] = rd;
}

void exec_remu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp38;
	_tmp38 = rem_unsign(cpu, rs1, rs2);
	rd = _tmp38;
	cpu.regs[num_rd] = rd;
}

void exec_addi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp40;
	_tmp40 = sign_extend(cpu, imm, 12);
	Register _tmp41;
	_tmp41 = (rs1 + _tmp40);
	rd = _tmp41;
	cpu.regs[num_rd] = rd;
}

void exec_xori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp43;
	_tmp43 = sign_extend(cpu, imm, 12);
	Register _tmp44;
	_tmp44 = (rs1 ^ _tmp43);
	rd = _tmp44;
	cpu.regs[num_rd] = rd;
}

void exec_ori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp46;
	_tmp46 = sign_extend(cpu, imm, 12);
	Register _tmp47;
	_tmp47 = (rs1 | _tmp46);
	rd = _tmp47;
	cpu.regs[num_rd] = rd;
}

void exec_andi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp49;
	_tmp49 = sign_extend(cpu, imm, 12);
	Register _tmp50;
	_tmp50 = (rs1 & _tmp49);
	rd = _tmp50;
	cpu.regs[num_rd] = rd;
}

void exec_slti(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp52;
	_tmp52 = sign_extend(cpu, imm, 12);
	Register _tmp53;
	_tmp53 = less_signed(cpu, rs1, _tmp52);
	rd = ternary;
	cpu.regs[num_rd] = rd;
}

void exec_sltiu(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp55;
	_tmp55 = sign_extend(cpu, imm, 12);
	Register _tmp56;
	_tmp56 = less_unsign(cpu, rs1, _tmp55);
	rd = ternary;
	cpu.regs[num_rd] = rd;
}

