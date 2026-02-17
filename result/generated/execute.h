#ifndef EXECUTE_HEADER
#define EXECUTE_HEADER

	// Execution functions declarations
	void exec_add(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sub(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_xor(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_or(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_and(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_slt(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sltu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sll(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_srl(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_sra(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mul(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulh(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulhsu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_mulhu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_div(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_divu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_rem(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_remu(SPU& spu, Register rd, Register rs1, Register rs2);
	void exec_addi(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_xori(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_ori(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_andi(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_slti(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_sltiu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_slli(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_srli(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_srai(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_jalr(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lb(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lh(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lw(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lbu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_lhu(SPU& spu, Register rd, Register rs1, Register imm);
	void exec_sb(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_sh(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_sw(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_beq(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bne(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_blt(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bge(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bltu(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_bgeu(SPU& spu, Register rs1, Register rs2, Register imm);
	void exec_lui(SPU& spu, Register rd, Register imm);
	void exec_auipc(SPU& spu, Register rd, Register imm);
	void exec_jal(SPU& spu, Register rd, Register imm);
	void exec_ecall(SPU& spu);
	void exec_fence(SPU& spu);

	void execute(SPU& spu, Instruction& insn);

#endif