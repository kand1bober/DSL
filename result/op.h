#include <cstdint>
#include <array>

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER 

struct CPU { std::array<uint32_t,32> regs; };

uint32_t bit_extract(CPU& cpu_regs, uint32_t src, uint8_t from, uint8_t to);

#endif
