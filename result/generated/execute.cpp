#include "op.h"

#include "execute.h"
#include "decode.h"

void execute(SPU& spu, Instruction& insn) {
	switch (insn.insn_type) {
		case ADD: {
			exec_add(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SUB: {
			exec_sub(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case XOR: {
			exec_xor(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case OR: {
			exec_or(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case AND: {
			exec_and(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLT: {
			exec_slt(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLTU: {
			exec_sltu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLL: {
			exec_sll(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SRL: {
			exec_srl(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SRA: {
			exec_sra(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case MUL: {
			exec_mul(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case MULH: {
			exec_mulh(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case MULHSU: {
			exec_mulhsu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case MULHU: {
			exec_mulhu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case DIV: {
			exec_div(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case DIVU: {
			exec_divu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case REM: {
			exec_rem(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case REMU: {
			exec_remu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case ADDI: {
			exec_addi(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case XORI: {
			exec_xori(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case ORI: {
			exec_ori(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case ANDI: {
			exec_andi(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLTI: {
			exec_slti(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLTIU: {
			exec_sltiu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SLLI: {
			exec_slli(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SRLI: {
			exec_srli(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SRAI: {
			exec_srai(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case JALR: {
			exec_jalr(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LB: {
			exec_lb(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LH: {
			exec_lh(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LW: {
			exec_lw(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LBU: {
			exec_lbu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LHU: {
			exec_lhu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SB: {
			exec_sb(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SH: {
			exec_sh(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case SW: {
			exec_sw(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BEQ: {
			exec_beq(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BNE: {
			exec_bne(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BLT: {
			exec_blt(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BGE: {
			exec_bge(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BLTU: {
			exec_bltu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case BGEU: {
			exec_bgeu(spu, insn.oprnds.arg1, insn.oprnds.arg2, insn.oprnds.arg3);
			break;
		}
		case LUI: {
			exec_lui(spu, insn.oprnds.arg1, insn.oprnds.arg2);
			break;
		}
		case AUIPC: {
			exec_auipc(spu, insn.oprnds.arg1, insn.oprnds.arg2);
			break;
		}
		case JAL: {
			exec_jal(spu, insn.oprnds.arg1, insn.oprnds.arg2);
			break;
		}
		throw std::runtime_error("Unknown enum: " + std::to_string(insn.insn_type));
	}
}

void exec_add(SPU &spu, Register par_rd, Register par_rs1, Register par_rs2) {
	std::cout << "add" << std::endl;
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
	std::cout << "sub" << std::endl;
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
	std::cout << "xor" << std::endl;
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
	std::cout << "or" << std::endl;
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
	std::cout << "and" << std::endl;
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
	std::cout << "slt" << std::endl;
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
	std::cout << "sltu" << std::endl;
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
	std::cout << "sll" << std::endl;
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
	std::cout << "srl" << std::endl;
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
	std::cout << "sra" << std::endl;
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
	std::cout << "mul" << std::endl;
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
	std::cout << "mulh" << std::endl;
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
	std::cout << "mulhsu" << std::endl;
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
	std::cout << "mulhu" << std::endl;
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
	std::cout << "div" << std::endl;
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
	std::cout << "divu" << std::endl;
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
	std::cout << "rem" << std::endl;
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
	std::cout << "remu" << std::endl;
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
	std::cout << "addi" << std::endl;
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
	std::cout << "xori" << std::endl;
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
	std::cout << "ori" << std::endl;
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
	std::cout << "andi" << std::endl;
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
	std::cout << "slti" << std::endl;
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
	std::cout << "sltiu" << std::endl;
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
	std::cout << "slli" << std::endl;
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
	std::cout << "srli" << std::endl;
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
	std::cout << "srai" << std::endl;
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
	std::cout << "jalr" << std::endl;
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
	std::cout << "lb" << std::endl;
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp89;
	_tmp89 = sign_extend(spu, imm, 12);
	Register _tmp90;
	_tmp90 = (rs1 + _tmp89);
	addr = _tmp90;
	Register _tmp92;
	_tmp92 = sign_extend(spu, readMem8(spu, addr), 8);
	rd = _tmp92;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lh(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	std::cout << "lh" << std::endl;
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp94;
	_tmp94 = sign_extend(spu, imm, 12);
	Register _tmp95;
	_tmp95 = (rs1 + _tmp94);
	addr = _tmp95;
	Register _tmp97;
	_tmp97 = sign_extend(spu, readMem16(spu, addr), 16);
	rd = _tmp97;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lw(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	std::cout << "lw" << std::endl;
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp99;
	_tmp99 = sign_extend(spu, imm, 12);
	Register _tmp100;
	_tmp100 = (rs1 + _tmp99);
	addr = _tmp100;
	rd = readMem32(spu, addr);
	spu.cpu.regs[par_rd] = rd;
}

void exec_lbu(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	std::cout << "lbu" << std::endl;
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp102;
	_tmp102 = sign_extend(spu, imm, 12);
	Register _tmp103;
	_tmp103 = (rs1 + _tmp102);
	addr = _tmp103;
	Register _tmp105;
	_tmp105 = zero_extend(spu, readMem8(spu, addr), 8);
	rd = _tmp105;
	spu.cpu.regs[par_rd] = rd;
}

void exec_lhu(SPU &spu, Register par_rd, Register par_rs1, Register par_imm) {
	std::cout << "lhu" << std::endl;
	Register rd;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp107;
	_tmp107 = sign_extend(spu, imm, 12);
	Register _tmp108;
	_tmp108 = (rs1 + _tmp107);
	addr = _tmp108;
	Register _tmp110;
	_tmp110 = zero_extend(spu, readMem16(spu, addr), 16);
	rd = _tmp110;
	spu.cpu.regs[par_rd] = rd;
}

void exec_sb(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "sb" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp112;
	_tmp112 = sign_extend(spu, imm, 12);
	Register _tmp113;
	_tmp113 = (rs1 + _tmp112);
	addr = _tmp113;
	Register _tmp114;
	_tmp114 = writeMem8(spu, addr, rs2);
}

void exec_sh(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "sh" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp116;
	_tmp116 = sign_extend(spu, imm, 12);
	Register _tmp117;
	_tmp117 = (rs1 + _tmp116);
	addr = _tmp117;
	Register _tmp118;
	_tmp118 = writeMem16(spu, addr, rs2);
}

void exec_sw(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "sw" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register addr;
	Register _tmp120;
	_tmp120 = sign_extend(spu, imm, 12);
	Register _tmp121;
	_tmp121 = (rs1 + _tmp120);
	addr = _tmp121;
	Register _tmp122;
	_tmp122 = writeMem32(spu, addr, rs2);
}

void exec_beq(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "beq" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp123;
	_tmp123 = (rs1 == rs2);
	Register _tmp125;
	_tmp125 = (imm << 1);
	Register _tmp127;
	_tmp127 = sign_extend(spu, _tmp125, 13);
	Register _tmp129;
	_tmp129 = ((bool)_tmp123) ? (_tmp127) : (0);
	Register _tmp130;
	_tmp130 = (pc + _tmp129);
	pc = _tmp130;
	spu.cpu.pc = pc;
}

void exec_bne(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "bne" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp131;
	_tmp131 = (rs1 != rs2);
	Register _tmp133;
	_tmp133 = (imm << 1);
	Register _tmp135;
	_tmp135 = sign_extend(spu, _tmp133, 13);
	Register _tmp137;
	_tmp137 = ((bool)_tmp131) ? (_tmp135) : (0);
	Register _tmp138;
	_tmp138 = (pc + _tmp137);
	pc = _tmp138;
	spu.cpu.pc = pc;
}

void exec_blt(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "blt" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp139;
	_tmp139 = less_signed(spu, rs1, rs2);
	Register _tmp141;
	_tmp141 = (imm << 1);
	Register _tmp143;
	_tmp143 = sign_extend(spu, _tmp141, 13);
	Register _tmp145;
	_tmp145 = ((bool)_tmp139) ? (_tmp143) : (0);
	Register _tmp146;
	_tmp146 = (pc + _tmp145);
	pc = _tmp146;
	spu.cpu.pc = pc;
}

void exec_bge(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "bge" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp147;
	_tmp147 = more_equal_signed(spu, rs1, rs2);
	Register _tmp149;
	_tmp149 = (imm << 1);
	Register _tmp151;
	_tmp151 = sign_extend(spu, _tmp149, 13);
	Register _tmp153;
	_tmp153 = ((bool)_tmp147) ? (_tmp151) : (0);
	Register _tmp154;
	_tmp154 = (pc + _tmp153);
	pc = _tmp154;
	spu.cpu.pc = pc;
}

void exec_bltu(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "bltu" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp155;
	_tmp155 = less_unsign(spu, rs1, rs2);
	Register _tmp157;
	_tmp157 = (imm << 1);
	Register _tmp159;
	_tmp159 = sign_extend(spu, _tmp157, 13);
	Register _tmp161;
	_tmp161 = ((bool)_tmp155) ? (_tmp159) : (0);
	Register _tmp162;
	_tmp162 = (pc + _tmp161);
	pc = _tmp162;
	spu.cpu.pc = pc;
}

void exec_bgeu(SPU &spu, Register par_rs1, Register par_rs2, Register par_imm) {
	std::cout << "bgeu" << std::endl;
	Register rs1;
	rs1 = spu.cpu.regs[par_rs1];
	Register rs2;
	rs2 = spu.cpu.regs[par_rs2];
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp163;
	_tmp163 = more_equal_unsign(spu, rs1, rs2);
	Register _tmp165;
	_tmp165 = (imm << 1);
	Register _tmp167;
	_tmp167 = sign_extend(spu, _tmp165, 13);
	Register _tmp169;
	_tmp169 = ((bool)_tmp163) ? (_tmp167) : (0);
	Register _tmp170;
	_tmp170 = (pc + _tmp169);
	pc = _tmp170;
	spu.cpu.pc = pc;
}

void exec_lui(SPU &spu, Register par_rd, Register par_imm) {
	std::cout << "lui" << std::endl;
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp172;
	_tmp172 = (imm << 12);
	rd = _tmp172;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

void exec_auipc(SPU &spu, Register par_rd, Register par_imm) {
	std::cout << "auipc" << std::endl;
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp174;
	_tmp174 = (imm << 12);
	Register _tmp175;
	_tmp175 = (pc + _tmp174);
	rd = _tmp175;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

void exec_jal(SPU &spu, Register par_rd, Register par_imm) {
	std::cout << "jal" << std::endl;
	Register rd;
	Register imm;
	imm = par_imm;
	Register pc;
	pc = spu.cpu.pc;
	Register _tmp177;
	_tmp177 = (pc + 4);
	rd = _tmp177;
	Register _tmp179;
	_tmp179 = (imm << 1);
	Register _tmp181;
	_tmp181 = sign_extend(spu, _tmp179, 21);
	Register _tmp182;
	_tmp182 = (pc + _tmp181);
	pc = _tmp182;
	spu.cpu.regs[par_rd] = rd;
	spu.cpu.pc = pc;
}

