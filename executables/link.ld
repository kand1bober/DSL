OUTPUT_ARCH(riscv)
ENTRY(_start)

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 128M 
}

SECTIONS
{
  .text : {
    *(.text._start)
    *(.text*)
  } > ram

  .rodata : {
    *(.rodata*)
  } > ram

  .data : {
    *(.data*)
  } > ram

  .bss : {
    *(.bss*)
  } > ram

  .stack (NOLOAD) : {
    . = ALIGN(16);
    _stack_top = . + 4K;
  } > ram
}