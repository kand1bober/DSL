
.include "macros.inc"
.section .text
.globl _start
_start:

	li x1, 0
	li x3, 0
	li x4, 0
	li x5, 0
	li x6, 0
	li x7, 0
	li x8, 0
	li x9, 0
	li x10, 0
	li x11, -79
	li x12, -44
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
	li t2, -123
	bne a4, t2, _fail

_pass:
    li a0, 0
    li a7, 93
    ecall

_fail:
    mv a0, gp
    li a7, 93
    ecall
