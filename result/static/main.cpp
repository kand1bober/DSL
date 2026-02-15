#include <iostream>
#include <iomanip>
#include "op.h"
#include "interpret.h"

int main(int argc, char* argv[])
{
    SPU spu{};

    if (argc != 2) {
        std::cout << "Correct usage: sim executables/<filename>" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    spu.load_elf(argv[1]);

    spu.run();

    // Проверяем результаты
    std::cout << "mem[0] = " << readMem32(spu, 0) << " (ожидается 3)" << std::endl;
    std::cout << "mem[4] = " << *((uint32_t*)&spu.mem.data[4]) << " (ожидается 7)" << std::endl; 
    std::cout << "mem[8] = " << *((uint32_t*)&spu.mem.data[8]) << " (ожидается 14)" << std::endl;

    // for (int i = 0; i < 32;) {
    //     for (int j = 0; j < 4; j++, i++) {
    //         std::cout << std::setw(3) <<  i << ": " << spu.cpu.regs[i] << ", ";
    //     }
    //     std::cout << "\n";
    // }

    return 0;
}
