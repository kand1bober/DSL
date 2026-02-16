#include <stdbool.h>
#include <stdexcept>

#include "spu.h"
#include "../generated/decode.h"
#include "../generated/execute.h"

#ifndef OPERATIONS_HEADER
#define OPERATIONS_HEADER

Register bit_extract(SPU& spu, int64_t src, Register from, Register to);

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

Register readMem8(SPU& spu, uint32_t addr);
Register readMem16(SPU& spu, uint32_t addr);
Register readMem32(SPU& spu, uint32_t addr);

Register writeMem8(SPU& spu, uint32_t addr, Register val);
Register writeMem16(SPU& spu, uint32_t addr, Register val);
Register writeMem32(SPU& spu, uint32_t addr, Register val);

#endif
