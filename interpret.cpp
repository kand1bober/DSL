#include <cstdint>
#include <array>
struct CPU { std::array<uint32_t,32> regs; };

void exec_add(CPU &cpu, num_rd, num_rs1, num_rs2) {
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

void exec_sub(CPU &cpu, num_rd, num_rs1, num_rs2) {
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

