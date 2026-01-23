#include <cstdint>
#include <array>
#include <stdbool.h>

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

struct CPU { std::array<uint32_t,32> regs; };

uint32_t bit_extract(CPU& cpu_regs, uint32_t src, uint8_t from, uint8_t to);

bool less_signed(CPU& cpu_regs, uint32_t a, uint32_t b);
bool more_signed(CPU& cpu_regs, uint32_t a, uint32_t b);
bool less_unsign(CPU& cpu_regs, uint32_t a, uint32_t b);
bool more_unsign(CPU& cpu_regs, uint32_t a, uint32_t b);

uint32_t op_sra(CPU& cpu_regs, uint32_t a, uint32_t b);

#endif
