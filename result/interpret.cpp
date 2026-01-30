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
	Register _tmp8;
	_tmp8 = ((bool)_tmp5) ? (1) : (0);
	rd = _tmp8;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp9;
	_tmp9 = less_unsign(cpu, rs1, rs2);
	Register _tmp12;
	_tmp12 = ((bool)_tmp9) ? (1) : (0);
	rd = _tmp12;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp15;
	_tmp15 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp16;
	_tmp16 = (rs1 << _tmp15);
	rd = _tmp16;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp19;
	_tmp19 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp20;
	_tmp20 = (rs1 >> _tmp19);
	rd = _tmp20;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp23;
	_tmp23 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp24;
	_tmp24 = op_sra(cpu, rs1, _tmp23);
	rd = _tmp24;
	cpu.regs[num_rd] = rd;
}

void exec_mul(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp25;
	_tmp25 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp28;
	_tmp28 = bit_extract(cpu, _tmp25, 31, 0);
	rd = _tmp28;
	cpu.regs[num_rd] = rd;
}

void exec_mulh(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp29;
	_tmp29 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp32;
	_tmp32 = bit_extract(cpu, _tmp29, 63, 32);
	rd = _tmp32;
	cpu.regs[num_rd] = rd;
}

void exec_mulhsu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp33;
	_tmp33 = ((SignedRegister)(rs1) * (Register)(rs2));
	Register _tmp36;
	_tmp36 = bit_extract(cpu, _tmp33, 63, 32);
	rd = _tmp36;
	cpu.regs[num_rd] = rd;
}

void exec_mulhu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp37;
	_tmp37 = ((Register)(rs1) * (Register)(rs2));
	Register _tmp40;
	_tmp40 = bit_extract(cpu, _tmp37, 63, 32);
	rd = _tmp40;
	cpu.regs[num_rd] = rd;
}

void exec_div(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp41;
	_tmp41 = div_signed(cpu, rs1, rs2);
	rd = _tmp41;
	cpu.regs[num_rd] = rd;
}

void exec_divu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp42;
	_tmp42 = div_unsign(cpu, rs1, rs2);
	rd = _tmp42;
	cpu.regs[num_rd] = rd;
}

void exec_rem(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp43;
	_tmp43 = rem_signed(cpu, rs1, rs2);
	rd = _tmp43;
	cpu.regs[num_rd] = rd;
}

void exec_remu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp44;
	_tmp44 = rem_unsign(cpu, rs1, rs2);
	rd = _tmp44;
	cpu.regs[num_rd] = rd;
}

void exec_addi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp46;
	_tmp46 = sign_extend(cpu, imm, 12);
	Register _tmp47;
	_tmp47 = (rs1 + _tmp46);
	rd = _tmp47;
	cpu.regs[num_rd] = rd;
}

void exec_xori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp49;
	_tmp49 = sign_extend(cpu, imm, 12);
	Register _tmp50;
	_tmp50 = (rs1 ^ _tmp49);
	rd = _tmp50;
	cpu.regs[num_rd] = rd;
}

void exec_ori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp52;
	_tmp52 = sign_extend(cpu, imm, 12);
	Register _tmp53;
	_tmp53 = (rs1 | _tmp52);
	rd = _tmp53;
	cpu.regs[num_rd] = rd;
}

void exec_andi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp55;
	_tmp55 = sign_extend(cpu, imm, 12);
	Register _tmp56;
	_tmp56 = (rs1 & _tmp55);
	rd = _tmp56;
	cpu.regs[num_rd] = rd;
}

void exec_slti(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp58;
	_tmp58 = sign_extend(cpu, imm, 12);
	Register _tmp59;
	_tmp59 = less_signed(cpu, rs1, _tmp58);
	Register _tmp62;
	_tmp62 = ((bool)_tmp59) ? (1) : (0);
	rd = _tmp62;
	cpu.regs[num_rd] = rd;
}

void exec_sltiu(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp64;
	_tmp64 = sign_extend(cpu, imm, 12);
	Register _tmp65;
	_tmp65 = less_unsign(cpu, rs1, _tmp64);
	Register _tmp68;
	_tmp68 = ((bool)_tmp65) ? (1) : (0);
	rd = _tmp68;
	cpu.regs[num_rd] = rd;
}

