#include <stdint.h>
#include <cassert>
#include "op.h"
#include "spu.h"

Register bit_extract(SPU& spu, Register src, Register from, Register to)
{
    Register mask = (((int64_t)1 << (from - to + 1)) - 1) << to;
        
    return (src & mask) >> to;
}

//----- MORE, LESS -----
bool less_signed(SPU& spu, Register a, Register b) {
    return (int32_t)a < (int32_t)b;
}

bool more_equal_signed(SPU& spu, Register a, Register b) {
    return (int32_t)a >= (int32_t)b;
}

bool less_unsign(SPU& spu, Register a, Register b) {
    return a < b;
}

bool more_equal_unsign(SPU& spu, Register a, Register b) {
    return a >= b;
}

//----- DIV -----
Register div_signed(SPU& spu, Register a, Register b) {
    assert(b);
    return (int32_t)a / (int32_t)b;
}

Register div_unsign(SPU& spu, Register a, Register b) {
    assert(b);
    return a / b;    
}

Register rem_signed(SPU& spu, Register a, Register b) {
    assert(b);
    return (int32_t)a % (int32_t)b;
}

Register rem_unsign(SPU& spu, Register a, Register b) {
    assert(b);
    return a % b;
}

// operation '>>>' in code tree is sra(shift right ariphmetic)
Register op_sra(SPU& spu, Register a, Register b) {
    return (int32_t)a >> b;
}   


Register sign_extend(SPU& spu, Register a, Register b) {
    if (a & ((Register)1 << (b - 1))) { //older bit == 1
        Register mask = ~(((Register)1 << b) - 1);
        a |= mask;
    }

    return a;
}

Register zero_extend(SPU& spu, Register a, Register b) {
    return a;
}   

Register readMem8(SPU& spu, uint32_t addr) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 1);
    return *(uint8_t*)((char*)(&spu.mem.data[0]) + addr);
}

Register readMem16(SPU& spu, uint32_t addr) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 2);
    return *(uint16_t*)((char*)(&spu.mem.data[0]) + addr);
}

Register readMem32(SPU& spu, uint32_t addr) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 4);
    return *(uint32_t*)((char*)(&spu.mem.data[0]) + addr);
}


Register writeMem8(SPU& spu, uint32_t addr, Register val) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 1);
    *(uint8_t*)((char*)(&spu.mem.data[0]) + addr) = (uint8_t)val;
    return 0;
}

Register writeMem16(SPU& spu, uint32_t addr, Register val) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 2);
    *(uint16_t*)((char*)(&spu.mem.data[0]) + addr) = (uint16_t)val;
    return 0;
}

Register writeMem32(SPU& spu, uint32_t addr, Register val) {
    assert(addr >= 0 && addr < spu.mem.data.size() - 4);
    *(uint32_t*)((char*)(&spu.mem.data[0]) + addr) = val;
    return 0;
}
