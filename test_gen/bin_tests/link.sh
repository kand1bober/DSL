#!/bin/bash

riscv64-unknown-elf-gcc -nostdlib \
    -march=rv32im \
    -mabi=ilp32 \
    -T bin_tests/link.ld \
    $1.s -o $1.elf
