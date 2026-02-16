.section .text
.globl _start
_start:
    addi x5, x0, 0
    addi x6, x0, 1
    addi x7, x0, 10
    addi x8, x0, 0
    sw x5, 0(x0)
    sw x6, 4(x0)
fib_loop:
    add x9, x5, x6
    add x5, x0, x6
    add x6, x0, x9
    addi x10, x8, 2
    slli x10, x10, 2
    sw x9, 0(x10)
    addi x8, x8, 1
    blt x8, x7, fib_loop
loop:
    j loop