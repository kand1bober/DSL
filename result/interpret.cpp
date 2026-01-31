#include "op.h"

void exec_add(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp0;
	_tmp0 = (rs1 + rs2);
	rd = _tmp0;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sub(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp1;
	_tmp1 = (rs1 - rs2);
	rd = _tmp1;
	spu.cpu.regs[par_rd] = rd;
}

void exec_xor(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp2;
	_tmp2 = (rs1 ^ rs2);
	rd = _tmp2;
	spu.cpu.regs[par_rd] = rd;
}

void exec_or(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp3;
	_tmp3 = (rs1 | rs2);
	rd = _tmp3;
	spu.cpu.regs[par_rd] = rd;
}

void exec_and(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp4;
	_tmp4 = (rs1 & rs2);
	rd = _tmp4;
	spu.cpu.regs[par_rd] = rd;
}

void exec_slt(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp5;
	_tmp5 = less_signed(spu, rs1, rs2);
	Register _tmp8;
	_tmp8 = ((bool)_tmp5) ? (1) : (0);
	rd = _tmp8;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sltu(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp9;
	_tmp9 = less_unsign(spu, rs1, rs2);
	Register _tmp12;
	_tmp12 = ((bool)_tmp9) ? (1) : (0);
	rd = _tmp12;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sll(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp15;
	_tmp15 = bit_extract(spu, rs2, 4, 0);
	Register _tmp16;
	_tmp16 = (rs1 << _tmp15);
	rd = _tmp16;
	spu.cpu.regs[par_rd] = rd;
}

void exec_srl(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp19;
	_tmp19 = bit_extract(spu, rs2, 4, 0);
	Register _tmp20;
	_tmp20 = (rs1 >> _tmp19);
	rd = _tmp20;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sra(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp23;
	_tmp23 = bit_extract(spu, rs2, 4, 0);
	Register _tmp24;
	_tmp24 = op_sra(spu, rs1, _tmp23);
	rd = _tmp24;
	spu.cpu.regs[par_rd] = rd;
}

void exec_mul(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp25;
	_tmp25 = ((int32_t)(rs1) * (int32_t)(rs2));
	Register _tmp28;
	_tmp28 = bit_extract(spu, _tmp25, 31, 0);
	rd = _tmp28;
	spu.cpu.regs[par_rd] = rd;
}

void exec_mulh(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp29;
	_tmp29 = ((int32_t)(rs1) * (int32_t)(rs2));
	Register _tmp32;
	_tmp32 = bit_extract(spu, _tmp29, 63, 32);
	rd = _tmp32;
	spu.cpu.regs[par_rd] = rd;
}

void exec_mulhsu(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp33;
	_tmp33 = ((int32_t)(rs1) * (Register)(rs2));
	Register _tmp36;
	_tmp36 = bit_extract(spu, _tmp33, 63, 32);
	rd = _tmp36;
	spu.cpu.regs[par_rd] = rd;
}

void exec_mulhu(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp37;
	_tmp37 = ((Register)(rs1) * (Register)(rs2));
	Register _tmp40;
	_tmp40 = bit_extract(spu, _tmp37, 63, 32);
	rd = _tmp40;
	spu.cpu.regs[par_rd] = rd;
}

void exec_div(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp41;
	_tmp41 = div_signed(spu, rs1, rs2);
	rd = _tmp41;
	spu.cpu.regs[par_rd] = rd;
}

void exec_divu(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp42;
	_tmp42 = div_unsign(spu, rs1, rs2);
	rd = _tmp42;
	spu.cpu.regs[par_rd] = rd;
}

void exec_rem(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp43;
	_tmp43 = rem_signed(spu, rs1, rs2);
	rd = _tmp43;
	spu.cpu.regs[par_rd] = rd;
}

void exec_remu(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register _tmp44;
	_tmp44 = rem_unsign(spu, rs1, rs2);
	rd = _tmp44;
	spu.cpu.regs[par_rd] = rd;
}

void exec_addi(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp46;
	_tmp46 = sign_extend(spu, imm, 12);
	Register _tmp47;
	_tmp47 = (rs1 + _tmp46);
	rd = _tmp47;
	spu.cpu.regs[par_rd] = rd;
}

void exec_xori(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp49;
	_tmp49 = sign_extend(spu, imm, 12);
	Register _tmp50;
	_tmp50 = (rs1 ^ _tmp49);
	rd = _tmp50;
	spu.cpu.regs[par_rd] = rd;
}

void exec_ori(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp52;
	_tmp52 = sign_extend(spu, imm, 12);
	Register _tmp53;
	_tmp53 = (rs1 | _tmp52);
	rd = _tmp53;
	spu.cpu.regs[par_rd] = rd;
}

void exec_andi(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp55;
	_tmp55 = sign_extend(spu, imm, 12);
	Register _tmp56;
	_tmp56 = (rs1 & _tmp55);
	rd = _tmp56;
	spu.cpu.regs[par_rd] = rd;
}

void exec_slti(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp58;
	_tmp58 = sign_extend(spu, imm, 12);
	Register _tmp59;
	_tmp59 = less_signed(spu, rs1, _tmp58);
	Register _tmp62;
	_tmp62 = ((bool)_tmp59) ? (1) : (0);
	rd = _tmp62;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sltiu(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp64;
	_tmp64 = sign_extend(spu, imm, 12);
	Register _tmp65;
	_tmp65 = less_unsign(spu, rs1, _tmp64);
	Register _tmp68;
	_tmp68 = ((bool)_tmp65) ? (1) : (0);
	rd = _tmp68;
	spu.cpu.regs[par_rd] = rd;
}

void exec_slli(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp71;
	_tmp71 = bit_extract(spu, imm, 4, 0);
	Register _tmp72;
	_tmp72 = (rs1 << _tmp71);
	rd = _tmp72;
	spu.cpu.regs[par_rd] = rd;
}

void exec_srli(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp75;
	_tmp75 = bit_extract(spu, imm, 4, 0);
	Register _tmp76;
	_tmp76 = (rs1 >> _tmp75);
	rd = _tmp76;
	spu.cpu.regs[par_rd] = rd;
}

void exec_srai(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp79;
	_tmp79 = bit_extract(spu, imm, 4, 0);
	Register _tmp80;
	_tmp80 = op_sra(spu, rs1, _tmp79);
	rd = _tmp80;
	spu.cpu.regs[par_rd] = rd;
}

void exec_jalr(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp82;
	_tmp82 = (pc + 4);
	rd = _tmp82;
	Register _tmp84;
	_tmp84 = sign_extend(spu, imm, 12);
	Register _tmp85;
	_tmp85 = (rs1 + _tmp84);
	Register _tmp87;
	_tmp87 = (_tmp85 & -2);
	pc = _tmp87;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

void exec_lb(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp89;
	_tmp89 = sign_extend(spu, imm, 12);
	Register _tmp90;
	_tmp90 = (rs1 + _tmp89);
	Register _tmp92;
	_tmp92 = sign_extend(spu, *((uint8_t*)(_tmp90 + &spu.mem.data)), 8);
	rd = _tmp92;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lh(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp94;
	_tmp94 = sign_extend(spu, imm, 12);
	Register _tmp95;
	_tmp95 = (rs1 + _tmp94);
	Register _tmp97;
	_tmp97 = sign_extend(spu, *((uint16_t*)(_tmp95 + &spu.mem.data)), 16);
	rd = _tmp97;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lw(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp99;
	_tmp99 = sign_extend(spu, imm, 12);
	Register _tmp100;
	_tmp100 = (rs1 + _tmp99);
	rd = *((uint32_t*)(_tmp100 + &spu.mem.data));
	spu.cpu.regs[par_rd] = rd;
}

void exec_lbu(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp102;
	_tmp102 = sign_extend(spu, imm, 12);
	Register _tmp103;
	_tmp103 = (rs1 + _tmp102);
	Register _tmp105;
	_tmp105 = zero_extend(spu, *((uint8_t*)(_tmp103 + &spu.mem.data)), 8);
	rd = _tmp105;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lhu(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register _tmp107;
	_tmp107 = sign_extend(spu, imm, 12);
	Register _tmp108;
	_tmp108 = (rs1 + _tmp107);
	Register _tmp110;
	_tmp110 = zero_extend(spu, *((uint16_t*)(_tmp108 + &spu.mem.data)), 16);
	rd = _tmp110;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sb(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register _tmp112;
	_tmp112 = sign_extend(spu, imm, 12);
	Register _tmp113;
	_tmp113 = (rs1 + _tmp112);
	Register _tmp116;
	_tmp116 = bit_extract(spu, rs2, 7, 0);
	*((uint8_t*)(_tmp113 + &spu.mem.data)) = (uint8_t)(_tmp116);
}

void exec_sh(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register _tmp118;
	_tmp118 = sign_extend(spu, imm, 12);
	Register _tmp119;
	_tmp119 = (rs1 + _tmp118);
	Register _tmp122;
	_tmp122 = bit_extract(spu, rs2, 16, 0);
	*((uint16_t*)(_tmp119 + &spu.mem.data)) = (uint16_t)(_tmp122);
}

void exec_sw(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register _tmp124;
	_tmp124 = sign_extend(spu, imm, 12);
	Register _tmp125;
	_tmp125 = (rs1 + _tmp124);
	*((uint32_t*)(_tmp125 + &spu.mem.data)) = rs2;
}

void exec_beq(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp126;
	_tmp126 = (rs1 == rs2);
	Register _tmp128;
	_tmp128 = (imm << 1);
	Register _tmp130;
	_tmp130 = sign_extend(spu, _tmp128, 12);
	Register _tmp131;
	_tmp131 = (pc + _tmp130);
	if ((bool)_tmp126) {
		pc = _tmp131;
	};
	spu.cpu.pc = pc;
}

void exec_bne(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp132;
	_tmp132 = (rs1 != rs2);
	Register _tmp134;
	_tmp134 = (imm << 1);
	Register _tmp136;
	_tmp136 = sign_extend(spu, _tmp134, 12);
	Register _tmp137;
	_tmp137 = (pc + _tmp136);
	if ((bool)_tmp132) {
		pc = _tmp137;
	};
	spu.cpu.pc = pc;
}

void exec_blt(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp138;
	_tmp138 = less_signed(spu, rs1, rs2);
	Register _tmp140;
	_tmp140 = (imm << 1);
	Register _tmp142;
	_tmp142 = sign_extend(spu, _tmp140, 12);
	Register _tmp143;
	_tmp143 = (pc + _tmp142);
	if ((bool)_tmp138) {
		pc = _tmp143;
	};
	spu.cpu.pc = pc;
}

void exec_bge(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp144;
	_tmp144 = more_equal_signed(spu, rs1, rs2);
	Register _tmp146;
	_tmp146 = (imm << 1);
	Register _tmp148;
	_tmp148 = sign_extend(spu, _tmp146, 12);
	Register _tmp149;
	_tmp149 = (pc + _tmp148);
	if ((bool)_tmp144) {
		pc = _tmp149;
	};
	spu.cpu.pc = pc;
}

void exec_bltu(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp150;
	_tmp150 = less_unsign(spu, rs1, rs2);
	Register _tmp152;
	_tmp152 = (imm << 1);
	Register _tmp154;
	_tmp154 = sign_extend(spu, _tmp152, 12);
	Register _tmp155;
	_tmp155 = (pc + _tmp154);
	if ((bool)_tmp150) {
		pc = _tmp155;
	};
	spu.cpu.pc = pc;
}

void exec_bgeu(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp156;
	_tmp156 = more_equal_unsign(spu, rs1, rs2);
	Register _tmp158;
	_tmp158 = (imm << 1);
	Register _tmp160;
	_tmp160 = sign_extend(spu, _tmp158, 12);
	Register _tmp161;
	_tmp161 = (pc + _tmp160);
	if ((bool)_tmp156) {
		pc = _tmp161;
	};
	spu.cpu.pc = pc;
}

void exec_lui(SPU &spu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp163;
	_tmp163 = (imm << 12);
	rd = _tmp163;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

void exec_auipc(SPU &spu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp165;
	_tmp165 = (imm << 12);
	Register _tmp166;
	_tmp166 = (pc + _tmp165);
	rd = _tmp166;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

void exec_jal(SPU &spu, Register par_rd, Register par_imm) {
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp168;
	_tmp168 = (pc + 4);
	rd = _tmp168;
	Register _tmp170;
	_tmp170 = (imm << 1);
	Register _tmp172;
	_tmp172 = sign_extend(spu, _tmp170, 20);
	Register _tmp173;
	_tmp173 = (pc + _tmp172);
	pc = _tmp173;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

