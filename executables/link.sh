#!/bin/bash

riscv64-unknown-elf-gcc -nostdlib \
    -march=rv32im \
    -mabi=ilp32 \
    -T executables/link.ld \
    $1.s -o $1.elf
