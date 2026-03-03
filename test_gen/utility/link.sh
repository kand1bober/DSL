#!/bin/bash

riscv32-unknown-elf-gcc -nostdlib \
    -march=rv32im \
    -mabi=ilp32 \
    -I tmp \
    -T utility/link.ld \
    $1.s -o $1.elf
