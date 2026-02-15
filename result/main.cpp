#include <iostream>
#include <iomanip>
#include "op.h"
#include "interpreter.h"

int main(int argc, char* argv[])
{
    SPU spu{0};

    // spu.cpu.regs[5] = 1;
    // spu.cpu.regs[6] = 2;
    // std::vector<Register> program;

    std::vector<Register> program = {
       // Просто сложение двух чисел
        0x00100293,  // addi x5, x0, 1    // t0 = 1
        0x00200313,  // addi x6, x0, 2    // t1 = 2
        0x006282b3,  // add x5, x5, x6    // t0 = t0 + t1 = 3
        
        // Сохраняем результат
        0x00502023,  // sw x5, 0(x0)      // mem[0] = 3
        
        // Еще операции 
        0x00400313,  // addi x6, x0, 4    // t1 = 4 
        0x0062c2b3,  // xor x5, x5, x6    // t0 = t0 ^ t1 = 3 ^ 4 = 7
        
        // Сохраняем
        0x00502223,  // sw x5, 4(x0)      // mem[4] = 7 -- проблемная строка
        
        // Умножение
        0x00200393,  // addi x7, x0, 2    // t2 = 2
        0x02728333,  // mul x6, x5, x7    // t1 = t0 * t2 = 7 * 2 = 14
        
        // Сохраняем
        0x00602423,  // sw x6, 8(x0)      // mem[8] = 14
    };

    spu.run(program);

    // Проверяем результаты
    std::cout << "mem[0] = " << *((uint32_t*)&spu.mem.data[0]) << " (ожидается 3)" << std::endl;
    std::cout << "mem[4] = " << *((uint32_t*)&spu.mem.data[4]) << " (ожидается 7)" << std::endl; 
    std::cout << "mem[8] = " << *((uint32_t*)&spu.mem.data[8]) << " (ожидается 14)" << std::endl;

    for (int i = 0; i < 32;) {
        for (int j = 0; j < 4; j++, i++) {
            std::cout << std::setw(3) <<  i << ": " << spu.cpu.regs[i] << ", ";
        }
        std::cout << "\n";
    }

    return 0;
}
