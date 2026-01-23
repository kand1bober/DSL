#include <stdint.h>
#include "op.h"

uint32_t bit_extract(CPU& cpu_regs, uint32_t src, uint8_t from, uint8_t to)
{
    if (from < to || from > 31) {
        return 0; // Некорректные параметры
    }
    
    uint32_t mask = (((uint32_t)1 << (from - to + 1)) - 1) << to;
        
    return (src & mask) >> to;
}

bool less_signed(CPU& cpu_regs, uint32_t a, uint32_t b)
{
    return (int32_t)a < (int32_t)b;
}

bool more_equal_signed(CPU& cpu_regs, uint32_t a, uint32_t b)
{
    return (int32_t)a >= (int32_t)b;
}

bool less_unsign(CPU& cpu_regs, uint32_t a, uint32_t b)
{
    return (uint32_t)a < (uint32_t)b;
}

bool more_equal_unsign(CPU& cpu_regs, uint32_t a, uint32_t b)
{
    return (uint32_t)a >= (uint32_t)b;
}

// operation '>>>' in code tree is sra(shift right ariphmetic)
uint32_t op_sra(CPU& cpu_regs, uint32_t a, uint32_t b)
{

}

