#include <cstdint>
#include <array>
#include <stdbool.h>

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

typedef uint32_t Register;
typedef int32_t  SignedRegister;

struct CPU { std::array<Register,32> regs; };

Register bit_extract(CPU& cpu_regs, Register src, Register from, Register to);

bool less_signed(CPU& cpu_regs, Register a, Register b);
bool more_equal_signed(CPU& cpu_regs, Register a, Register b);
bool less_unsign(CPU& cpu_regs, Register a, Register b);
bool more_equal_unsign(CPU& cpu_regs, Register a, Register b);

Register div_signed(CPU& cpu_regs, Register a, Register b);
Register div_unsign(CPU& cpu_regs, Register a, Register b);
Register rem_signed(CPU& cpu_regs, Register a, Register b);
Register rem_unsign(CPU& cpu_regs, Register a, Register b);

Register op_sra(CPU& cpu_regs, Register a, Register b);

Register sign_extend(CPU& cpu_regs, Register a, Register b);

#endif
