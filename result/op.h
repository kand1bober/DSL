#include <cstdint>
#include <array>
#include <stdbool.h>
#include <stdexcept>
#include <vector>
#include <iostream>

#include "spu.h"
#include "decode.h"
#include "execute.h"


void SPU::run(const std::vector<Register>& program) {
    cpu.pc = 0;

    while (cpu.pc < program.size()) {
        //fetch
        uint32_t machine_word = program[cpu.pc]; //TODO: загрузка ELF'a

        //decode
        std::cout << "decoding: " << std::hex << machine_word << std::endl;
        Instruction insn = decode(*this, machine_word);

        //execute
        execute(*this, insn);

        //update pc 
        cpu.pc += 1;
    }
}

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER

Register bit_extract(SPU& spu, Register src, Register from, Register to);

bool less_signed(SPU& spu, Register a, Register b);
bool more_equal_signed(SPU& spu, Register a, Register b);
bool less_unsign(SPU& spu, Register a, Register b);
bool more_equal_unsign(SPU& spu, Register a, Register b);

Register div_signed(SPU& spu, Register a, Register b);
Register div_unsign(SPU& spu, Register a, Register b);
Register rem_signed(SPU& spu, Register a, Register b);
Register rem_unsign(SPU& spu, Register a, Register b);

Register op_sra(SPU& spu, Register a, Register b);

Register sign_extend(SPU& spu, Register a, Register b);
Register zero_extend(SPU& spu, Register a, Register b);

Register readMem8(SPU& spu, uint32_t addr);
Register readMem16(SPU& spu, uint32_t addr);
Register readMem32(SPU& spu, uint32_t addr);

Register writeMem8(SPU& spu, uint32_t addr, Register val);
Register writeMem16(SPU& spu, uint32_t addr, Register val);
Register writeMem32(SPU& spu, uint32_t addr, Register val);

#endif
