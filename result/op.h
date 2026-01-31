#include <cstdint>
#include <array>
#include <stdbool.h>

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

typedef uint32_t Register;
typedef int32_t  SignedRegister;

struct CPU { 
    std::array<Register, 32> regs; 
    Register pc;
};

struct Ram {
    std::array<Register, 1024> data;
};

class SPU {
public:
    CPU cpu;
    Ram mem;
};

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

#endif
