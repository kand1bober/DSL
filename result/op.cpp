#include <stdint.h>
#include "op.h"

Register bit_extract(SPU& spu, Register src, Register from, Register to)
{
    Register mask = (((Register)1 << (from - to + 1)) - 1) << to;
        
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
    return (int32_t)a / (int32_t)b;
}

Register div_unsign(SPU& spu, Register a, Register b) {
    return a / b;    
}

Register rem_signed(SPU& spu, Register a, Register b) {
    return (int32_t)a % (int32_t)b;
}

Register rem_unsign(SPU& spu, Register a, Register b) {
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
