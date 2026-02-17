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
        std::cout << std::hex << "pc: " << cpu.pc << std::endl;
        uint32_t machine_word;
        memcpy(&machine_word, &program[cpu.pc], 4);
        std::cout << "machine word: " << std::hex << machine_word << std::endl;

        //decode
        Instruction insn = decode(*this, machine_word);

        //save pc
        cpu.old_pc = cpu.pc;

        //execute
        execute(*this, insn);
        cpu.regs[0] = 0; //set x0

        // for (int i = 0; i < 32;) {
        //     for (int j = 0; j < 4; j++, i++) {
        //         std::cout << std::setw(5) << std::dec << i << ": " << cpu.regs[i] << ", ";
        //     }
        //     std::cout << "\n";
        // }

        //update pc 
        //TODO: непонятно как сгенерировать это условие, пока написано вручную
        if (!(insn.insn_type == JAL)) {
            if (insn.insn_type >= BEQ && insn.insn_type <= BGEU) {
                if (cpu.old_pc == cpu.pc)
                    cpu.pc += 4;
            }    
            else 
                cpu.pc += 4;
        } 
    }
}

void SPU::load_elf(const std::string& filename) {
    ELFIO::elfio reader;
    if (!reader.load(filename)) {
        throw std::runtime_error("Failed to load ELF");
    }

    uint32_t min_addr = 0x80000000;
    uint32_t max_addr = 0;
    
    // Find borders of memory
    for (int i = 0; i < reader.segments.size(); i++) {
        const ELFIO::segment* pseg = reader.segments[i];
        if (pseg->get_type() == ELFIO::PT_LOAD) {
            ELFIO::Elf64_Addr vaddr = pseg->get_virtual_address();
            ELFIO::Elf64_Word memsz = pseg->get_memory_size();
            
            if (vaddr < min_addr) min_addr = vaddr;
            if (vaddr + memsz > max_addr) max_addr = vaddr + memsz;
        }
    }
    
    program.resize(max_addr - min_addr);
    uint32_t base_addr = min_addr;
    
    std::cout << "Memory: [" << std::hex << min_addr << "-" << max_addr 
              << "], size: " << std::dec << max_addr - min_addr << " bytes" << std::endl;
    
    // Load segments
    for (int i = 0; i < reader.segments.size(); i++) {
        const ELFIO::segment* pseg = reader.segments[i];
        if (pseg->get_type() == ELFIO::PT_LOAD) {
            ELFIO::Elf64_Addr vaddr = pseg->get_virtual_address();
            ELFIO::Elf64_Word filesz = pseg->get_file_size();
            ELFIO::Elf64_Word memsz = pseg->get_memory_size();
            const char* data = pseg->get_data();
            
            uint32_t offset = vaddr - base_addr;
            
            // Копируем данные
            for (size_t j = 0; j < filesz; ++j) {
                program[offset + j] = data[j];
            }
            
            // BSS заполняем нулями
            for (size_t j = filesz; j < memsz; ++j) {
                program[offset + j] = 0;
            }
        }
    }

    cpu.pc = reader.get_entry() - base_addr;
}

#endif  
