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
	_tmp5 = less_signed(cpu, num_rs1, num_rs2);
	Register _tmp6;
	_tmp6 = ((bool)_tmp5) ? 1 : 0;
	rd = _tmp6;
	cpu.regs[num_rd] = rd;
}

void exec_sltu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp7;
	_tmp7 = less_unsign(cpu, num_rs1, num_rs2);
	Register _tmp8;
	_tmp8 = ((bool)_tmp7) ? 1 : 0;
	rd = _tmp8;
	cpu.regs[num_rd] = rd;
}

void exec_sll(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp11;
	_tmp11 = bit_extract(cpu, num_rs2, 4, 0);
	Register _tmp12;
	_tmp12 = (rs1 << _tmp11);
	rd = _tmp12;
	cpu.regs[num_rd] = rd;
}

void exec_srl(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp15;
	_tmp15 = bit_extract(cpu, num_rs2, 4, 0);
	Register _tmp16;
	_tmp16 = (rs1 >> _tmp15);
	rd = _tmp16;
	cpu.regs[num_rd] = rd;
}

void exec_sra(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp19;
	_tmp19 = bit_extract(cpu, num_rs2, 4, 0);
	Register _tmp20;
	_tmp20 = op_sra(cpu, num_rs1, _tmp19);
	rd = _tmp20;
	cpu.regs[num_rd] = rd;
}

void exec_mul(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp21;
	_tmp21 = (SignedRegister)(rs1);
	Register _tmp22;
	_tmp22 = (SignedRegister)(rs2);
	Register _tmp23;
	_tmp23 = (_tmp21 * _tmp22);
	Register _tmp26;
	_tmp26 = bit_extract(cpu, _tmp23, 31, 0);
	rd = _tmp26;
	cpu.regs[num_rd] = rd;
}

void exec_mulh(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp27;
	_tmp27 = (SignedRegister)(rs1);
	Register _tmp28;
	_tmp28 = (SignedRegister)(rs2);
	Register _tmp29;
	_tmp29 = (_tmp27 * _tmp28);
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
	_tmp33 = (SignedRegister)(rs1);
	Register _tmp34;
	_tmp34 = (Register)(rs2);
	Register _tmp35;
	_tmp35 = (_tmp33 * _tmp34);
	Register _tmp38;
	_tmp38 = bit_extract(cpu, _tmp35, 63, 32);
	rd = _tmp38;
	cpu.regs[num_rd] = rd;
}

void exec_mulhu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp39;
	_tmp39 = (Register)(rs1);
	Register _tmp40;
	_tmp40 = (Register)(rs2);
	Register _tmp41;
	_tmp41 = (_tmp39 * _tmp40);
	Register _tmp44;
	_tmp44 = bit_extract(cpu, _tmp41, 63, 32);
	rd = _tmp44;
	cpu.regs[num_rd] = rd;
}

void exec_div(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp45;
	_tmp45 = div_signed(cpu, num_rs1, num_rs2);
	rd = _tmp45;
	cpu.regs[num_rd] = rd;
}

void exec_divu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp46;
	_tmp46 = div_unsign(cpu, num_rs1, num_rs2);
	rd = _tmp46;
	cpu.regs[num_rd] = rd;
}

void exec_rem(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp47;
	_tmp47 = rem_signed(cpu, num_rs1, num_rs2);
	rd = _tmp47;
	cpu.regs[num_rd] = rd;
}

void exec_remu(CPU &cpu, Register num_rd, Register num_rs1, Register num_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register rs2;
	rs2 = cpu.regs[num_rs2];
	Register _tmp48;
	_tmp48 = rem_unsign(cpu, num_rs1, num_rs2);
	rd = _tmp48;
	cpu.regs[num_rd] = rd;
}

void exec_addi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp50;
	_tmp50 = sign_extend(cpu, num_imm, 12);
	Register _tmp51;
	_tmp51 = (rs1 + _tmp50);
	rd = _tmp51;
	cpu.regs[num_rd] = rd;
}

void exec_xori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp53;
	_tmp53 = sign_extend(cpu, num_imm, 12);
	Register _tmp54;
	_tmp54 = (rs1 ^ _tmp53);
	rd = _tmp54;
	cpu.regs[num_rd] = rd;
}

void exec_ori(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp56;
	_tmp56 = sign_extend(cpu, num_imm, 12);
	Register _tmp57;
	_tmp57 = (rs1 | _tmp56);
	rd = _tmp57;
	cpu.regs[num_rd] = rd;
}

void exec_andi(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp59;
	_tmp59 = sign_extend(cpu, num_imm, 12);
	Register _tmp60;
	_tmp60 = (rs1 & _tmp59);
	rd = _tmp60;
	cpu.regs[num_rd] = rd;
}

void exec_slti(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp62;
	_tmp62 = sign_extend(cpu, num_imm, 12);
	Register _tmp63;
	_tmp63 = less_signed(cpu, num_rs1, _tmp62);
	Register _tmp64;
	_tmp64 = ((bool)_tmp63) ? 1 : 0;
	rd = _tmp64;
	cpu.regs[num_rd] = rd;
}

void exec_sltiu(CPU &cpu, Register num_rd, Register num_rs1, Register num_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[num_rs1];
	Register imm;
	imm = num_imm;
	Register _tmp66;
	_tmp66 = sign_extend(cpu, num_imm, 12);
	Register _tmp67;
	_tmp67 = less_unsign(cpu, num_rs1, _tmp66);
	Register _tmp68;
	_tmp68 = ((bool)_tmp67) ? 1 : 0;
	rd = _tmp68;
	cpu.regs[num_rd] = rd;
}

