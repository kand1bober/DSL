
.include "macros.inc"
.section .text
.globl _start
_start:

_state_init_:
	li x1, 0
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, 86
	li x12, -86
	li x13, 0
	li x15, 0
	li x16, 0
	li x17, 0
	li x18, 0
	li x19, 0
	li x20, 0
	li x21, 0
	li x22, 0
	li x23, 0
	li x24, 0
	li x25, 0
	li x26, 0
	li x27, 0
	li x28, 0
	li x29, 0
	li x30, 0
	li x31, 0

	add x14, x11, x12

_state_check_:
	li x7, 0
	bne x1, x7, _fail
	li x7, 0
	bne x3, x7, _fail
	li x7, 0
	bne x4, x7, _fail
	li x7, 0
	bne x5, x7, _fail
	li x7, 0
	bne x6, x7, _fail
	li x7, 0
	bne x7, x7, _fail
	li x7, 0
	bne x8, x7, _fail
	li x7, 0
	bne x9, x7, _fail
	li x7, 0
	bne x10, x7, _fail
	li x7, 86
	bne x11, x7, _fail
	li x7, -86
	bne x12, x7, _fail
	li x7, 0
	bne x13, x7, _fail
	li x7, 0
	bne x14, x7, _fail
	li x7, 0
	bne x15, x7, _fail
	li x7, 0
	bne x16, x7, _fail
	li x7, 0
	bne x17, x7, _fail
	li x7, 0
	bne x18, x7, _fail
	li x7, 0
	bne x19, x7, _fail
	li x7, 0
	bne x20, x7, _fail
	li x7, 0
	bne x21, x7, _fail
	li x7, 0
	bne x22, x7, _fail
	li x7, 0
	bne x23, x7, _fail
	li x7, 0
	bne x24, x7, _fail
	li x7, 0
	bne x25, x7, _fail
	li x7, 0
	bne x26, x7, _fail
	li x7, 0
	bne x27, x7, _fail
	li x7, 0
	bne x28, x7, _fail
	li x7, 0
	bne x29, x7, _fail
	li x7, 0
	bne x30, x7, _fail
	li x7, 0
	bne x31, x7, _fail

_pass:
    li a0, 0
    li a7, 93
    ecall

_fail:
    mv a0, gp
    li a7, 93
    ecall
