
.include "macros.inc"
.section .text
.globl _start
_start:

_begin_test_0:
	li gp,0
	li a1, -7
	li a2, -25
	add a4, a1, a2
	li t2, -32
	bne a4, t2, _fail

_pass:
    li a0, 0
    li a7, 93
    ecall

_fail:
    mv a0, gp
    li a7, 93
    ecall
