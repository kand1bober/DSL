#include "op.h"

void exec_add(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp0;
	_tmp0 = (rs1 + rs2);
	rd = _tmp0;
	cpu.regs[par_rd] = rd;
}

void exec_sub(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp1;
	_tmp1 = (rs1 - rs2);
	rd = _tmp1;
	cpu.regs[par_rd] = rd;
}

void exec_xor(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp2;
	_tmp2 = (rs1 ^ rs2);
	rd = _tmp2;
	cpu.regs[par_rd] = rd;
}

void exec_or(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp3;
	_tmp3 = (rs1 | rs2);
	rd = _tmp3;
	cpu.regs[par_rd] = rd;
}

void exec_and(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp4;
	_tmp4 = (rs1 & rs2);
	rd = _tmp4;
	cpu.regs[par_rd] = rd;
}

void exec_slt(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp5;
	_tmp5 = less_signed(cpu, rs1, rs2);
	Register _tmp8;
	_tmp8 = ((bool)_tmp5) ? (1) : (0);
	rd = _tmp8;
	cpu.regs[par_rd] = rd;
}

void exec_sltu(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp9;
	_tmp9 = less_unsign(cpu, rs1, rs2);
	Register _tmp12;
	_tmp12 = ((bool)_tmp9) ? (1) : (0);
	rd = _tmp12;
	cpu.regs[par_rd] = rd;
}

void exec_sll(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp15;
	_tmp15 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp16;
	_tmp16 = (rs1 << _tmp15);
	rd = _tmp16;
	cpu.regs[par_rd] = rd;
}

void exec_srl(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp19;
	_tmp19 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp20;
	_tmp20 = (rs1 >> _tmp19);
	rd = _tmp20;
	cpu.regs[par_rd] = rd;
}

void exec_sra(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp23;
	_tmp23 = bit_extract(cpu, rs2, 4, 0);
	Register _tmp24;
	_tmp24 = op_sra(cpu, rs1, _tmp23);
	rd = _tmp24;
	cpu.regs[par_rd] = rd;
}

void exec_mul(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp25;
	_tmp25 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp28;
	_tmp28 = bit_extract(cpu, _tmp25, 31, 0);
	rd = _tmp28;
	cpu.regs[par_rd] = rd;
}

void exec_mulh(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp29;
	_tmp29 = ((SignedRegister)(rs1) * (SignedRegister)(rs2));
	Register _tmp32;
	_tmp32 = bit_extract(cpu, _tmp29, 63, 32);
	rd = _tmp32;
	cpu.regs[par_rd] = rd;
}

void exec_mulhsu(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp33;
	_tmp33 = ((SignedRegister)(rs1) * (Register)(rs2));
	Register _tmp36;
	_tmp36 = bit_extract(cpu, _tmp33, 63, 32);
	rd = _tmp36;
	cpu.regs[par_rd] = rd;
}

void exec_mulhu(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp37;
	_tmp37 = ((Register)(rs1) * (Register)(rs2));
	Register _tmp40;
	_tmp40 = bit_extract(cpu, _tmp37, 63, 32);
	rd = _tmp40;
	cpu.regs[par_rd] = rd;
}

void exec_div(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp41;
	_tmp41 = div_signed(cpu, rs1, rs2);
	rd = _tmp41;
	cpu.regs[par_rd] = rd;
}

void exec_divu(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp42;
	_tmp42 = div_unsign(cpu, rs1, rs2);
	rd = _tmp42;
	cpu.regs[par_rd] = rd;
}

void exec_rem(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp43;
	_tmp43 = rem_signed(cpu, rs1, rs2);
	rd = _tmp43;
	cpu.regs[par_rd] = rd;
}

void exec_remu(CPU &cpu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register _tmp44;
	_tmp44 = rem_unsign(cpu, rs1, rs2);
	rd = _tmp44;
	cpu.regs[par_rd] = rd;
}

void exec_addi(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp46;
	_tmp46 = sign_extend(cpu, imm, 12);
	Register _tmp47;
	_tmp47 = (rs1 + _tmp46);
	rd = _tmp47;
	cpu.regs[par_rd] = rd;
}

void exec_xori(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp49;
	_tmp49 = sign_extend(cpu, imm, 12);
	Register _tmp50;
	_tmp50 = (rs1 ^ _tmp49);
	rd = _tmp50;
	cpu.regs[par_rd] = rd;
}

void exec_ori(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp52;
	_tmp52 = sign_extend(cpu, imm, 12);
	Register _tmp53;
	_tmp53 = (rs1 | _tmp52);
	rd = _tmp53;
	cpu.regs[par_rd] = rd;
}

void exec_andi(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp55;
	_tmp55 = sign_extend(cpu, imm, 12);
	Register _tmp56;
	_tmp56 = (rs1 & _tmp55);
	rd = _tmp56;
	cpu.regs[par_rd] = rd;
}

void exec_slti(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp58;
	_tmp58 = sign_extend(cpu, imm, 12);
	Register _tmp59;
	_tmp59 = less_signed(cpu, rs1, _tmp58);
	Register _tmp62;
	_tmp62 = ((bool)_tmp59) ? (1) : (0);
	rd = _tmp62;
	cpu.regs[par_rd] = rd;
}

void exec_sltiu(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp64;
	_tmp64 = sign_extend(cpu, imm, 12);
	Register _tmp65;
	_tmp65 = less_unsign(cpu, rs1, _tmp64);
	Register _tmp68;
	_tmp68 = ((bool)_tmp65) ? (1) : (0);
	rd = _tmp68;
	cpu.regs[par_rd] = rd;
}

void exec_slli(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp71;
	_tmp71 = bit_extract(cpu, imm, 4, 0);
	Register _tmp72;
	_tmp72 = (rs1 << _tmp71);
	rd = _tmp72;
	cpu.regs[par_rd] = rd;
}

void exec_srli(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp75;
	_tmp75 = bit_extract(cpu, imm, 4, 0);
	Register _tmp76;
	_tmp76 = (rs1 >> _tmp75);
	rd = _tmp76;
	cpu.regs[par_rd] = rd;
}

void exec_srai(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp79;
	_tmp79 = bit_extract(cpu, imm, 4, 0);
	Register _tmp80;
	_tmp80 = op_sra(cpu, rs1, _tmp79);
	rd = _tmp80;
	cpu.regs[par_rd] = rd;
}

void exec_jalr(CPU &cpu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp82;
	_tmp82 = (pc + 4);
	rd = _tmp82;
	Register _tmp84;
	_tmp84 = sign_extend(cpu, imm, 12);
	Register _tmp85;
	_tmp85 = (rs1 + _tmp84);
	Register _tmp87;
	_tmp87 = (_tmp85 & -2);
	pc = _tmp87;
	cpu.regs[par_rd] = rd;
	cpu.pc = pc;
}

void exec_beq(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp88;
	_tmp88 = (rs1 == rs2);
	Register _tmp90;
	_tmp90 = (imm << 1);
	Register _tmp92;
	_tmp92 = sign_extend(cpu, _tmp90, 12);
	Register _tmp93;
	_tmp93 = (pc + _tmp92);
	if ((bool)_tmp88) {
		pc = _tmp93;
	};
	cpu.pc = pc;
}

void exec_bne(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp94;
	_tmp94 = (rs1 != rs2);
	Register _tmp96;
	_tmp96 = (imm << 1);
	Register _tmp98;
	_tmp98 = sign_extend(cpu, _tmp96, 12);
	Register _tmp99;
	_tmp99 = (pc + _tmp98);
	if ((bool)_tmp94) {
		pc = _tmp99;
	};
	cpu.pc = pc;
}

void exec_blt(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp100;
	_tmp100 = less_signed(cpu, rs1, rs2);
	Register _tmp102;
	_tmp102 = (imm << 1);
	Register _tmp104;
	_tmp104 = sign_extend(cpu, _tmp102, 12);
	Register _tmp105;
	_tmp105 = (pc + _tmp104);
	if ((bool)_tmp100) {
		pc = _tmp105;
	};
	cpu.pc = pc;
}

void exec_bge(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp106;
	_tmp106 = more_equal_signed(cpu, rs1, rs2);
	Register _tmp108;
	_tmp108 = (imm << 1);
	Register _tmp110;
	_tmp110 = sign_extend(cpu, _tmp108, 12);
	Register _tmp111;
	_tmp111 = (pc + _tmp110);
	if ((bool)_tmp106) {
		pc = _tmp111;
	};
	cpu.pc = pc;
}

void exec_bltu(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp112;
	_tmp112 = less_unsign(cpu, rs1, rs2);
	Register _tmp114;
	_tmp114 = (imm << 1);
	Register _tmp116;
	_tmp116 = sign_extend(cpu, _tmp114, 12);
	Register _tmp117;
	_tmp117 = (pc + _tmp116);
	if ((bool)_tmp112) {
		pc = _tmp117;
	};
	cpu.pc = pc;
}

void exec_bgeu(CPU &cpu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = cpu.regs[par_rs1];
	Register rs2;
	rs2 = cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp118;
	_tmp118 = more_equal_unsign(cpu, rs1, rs2);
	Register _tmp120;
	_tmp120 = (imm << 1);
	Register _tmp122;
	_tmp122 = sign_extend(cpu, _tmp120, 12);
	Register _tmp123;
	_tmp123 = (pc + _tmp122);
	if ((bool)_tmp118) {
		pc = _tmp123;
	};
	cpu.pc = pc;
}

void exec_lui(CPU &cpu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp125;
	_tmp125 = (imm << 12);
	rd = _tmp125;
	cpu.regs[par_rd] = rd;
	cpu.pc = pc;
}

void exec_auipc(CPU &cpu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp127;
	_tmp127 = (imm << 12);
	Register _tmp128;
	_tmp128 = (pc + _tmp127);
	rd = _tmp128;
	cpu.regs[par_rd] = rd;
	cpu.pc = pc;
}

void exec_jal(CPU &cpu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = cpu.pc;
	Register _tmp130;
	_tmp130 = (pc + 4);
	rd = _tmp130;
	Register _tmp132;
	_tmp132 = (imm << 1);
	Register _tmp134;
	_tmp134 = sign_extend(cpu, _tmp132, 20);
	Register _tmp135;
	_tmp135 = (pc + _tmp134);
	pc = _tmp135;
	cpu.regs[par_rd] = rd;
	cpu.pc = pc;
}

