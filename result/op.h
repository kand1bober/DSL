#include <cstdint>
#include <array>

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

struct CPU { std::array<uint32_t,32> regs; };

uint32_t bit_extract(CPU& cpu_regs, uint32_t src, uint8_t from, uint8_t to);

uint32_t op_sra(CPU& cpu_regs, uint32_t a, uint32_t b);

#endif
