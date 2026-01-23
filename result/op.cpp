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
