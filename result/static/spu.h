#include <cstdint>
#include <array>
#include <vector>
#include <iostream>

#ifndef SPU_HEADER
#define SPU_HEADER

typedef uint32_t Register;
typedef int32_t  SignedRegister;

struct CPU { 
    std::array<Register, 32> regs;

    Register old_pc;
    Register pc;
};

struct Ram {
    std::array<uint8_t, 1 << 20> data;
};

class SPU {
public:
    CPU cpu;
    Ram mem;

    std::vector<uint8_t> program;

    void load_elf(const std::string& filename);
    void run();
};

#endif
