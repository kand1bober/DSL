#include <string>

#include <elfio/elfio.hpp>
#include "spu.h"
#include "../generated/decode.h"
#include "../generated/execute.h"

#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER

void SPU::run() {
    while (cpu.pc < program.size()) {
        //fetch
        std::cout << "pc: " << cpu.pc << std::endl;
        uint32_t machine_word;
        memcpy(&machine_word, &program[cpu.pc], 4);
        std::cout << "machine word: " << std::hex << machine_word << std::endl;

        //decode
        Instruction insn = decode(*this, machine_word);

        //execute
        execute(*this, insn);

        //update pc 
        //TODO: непонятно как сгенерировать это условие, пока написано вручную
        if (!(insn.insn_type >= BEQ && insn.insn_type <= JAL)) {
            cpu.pc += 4;
        }        
    }
}

void SPU::load_elf(const std::string& filename) {
    ELFIO::elfio reader;
    if (!reader.load(filename)) {
        throw std::runtime_error("Failed to load ELF");
    }

    ELFIO::Elf64_Word prog_size = 0;
    ELFIO::Elf_Half seg_num = reader.segments.size();
    for (int i = 0; i < seg_num; i++) {
        const ELFIO::segment* pseg = reader.segments[i];
    
        if (pseg->get_type() == ELFIO::PT_LOAD) {
            ELFIO::Elf64_Addr vaddr = pseg->get_virtual_address();
            ELFIO::Elf64_Word filesz = pseg->get_file_size();
            ELFIO::Elf64_Word memsz = pseg->get_memory_size();
            const char* data = pseg->get_data(); // Access segments's data

            // resize ram
            prog_size += memsz;
            program.resize(prog_size);    

            // std::cout << "Loading segment at 0x" << std::hex << vaddr 
            //           << ", size: " << std::dec << filesz 
            //           << " (file) / " << memsz << " (mem)" << std::endl;
            
            // Copy data to memory
            for (size_t j = 0; j < filesz; ++j) {
                program[vaddr + j] = data[j];
            }
            
            // BSS
            for (size_t j = filesz; j < memsz; ++j) {
                program[vaddr + j] = 0;
            }
        }
    }

    cpu.pc = reader.get_entry();
}

#endif  
