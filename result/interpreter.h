#include "spu.h"
#include "decode.h"
#include "execute.h"

#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER

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

#endif  