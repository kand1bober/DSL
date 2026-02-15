.section .text
.globl _start
_start:
    addi x5, x0, 1
    addi x6, x0, 2
    add x5, x5, x6
    sw x5, 0(x0)
    addi x6, x0, 4
    xor x5, x5, x6
    sw x5, 4(x0)
    addi x7, x0, 2
    mul x6, x5, x7
    sw x6, 8(x0)
loop:
    j loop