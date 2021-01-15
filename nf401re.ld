MEMORY
{
    FLASH (rx): ORIGIN = 0x8000000, LENGTH = 512K
    RAM (rwx): ORIGIN = 0x20000000, LENGTH = 96K
}

ENTRY(reset_handler)

SECTIONS
{
    .isr_vector :
    {
      . = ALIGN(4);
      KEEP(*(.isr_vector))
      . = ORIGIN(FLASH) + 512;
    } >FLASH
    .text :
    {
      *(.text)
      . = ALIGN(4);
      _etext = .;
    } > FLASH
    .data :
    {
      _sdata = .;
      *(.data*)
      _edata = .;
      . = ALIGN(4);
    } > RAM AT>FLASH
    .bss :
    {
      __bss_start__ = .;
      *(.bss)
      __bss_end__ = .;
    } > RAM

    /DISCARD/ :
    {
        *(.ARM.exidx*)
    }
    PROVIDE(_heap = __bss_end__);
    PROVIDE(_heap_end = _stack - _stack_size);
    PROVIDE(_stack_size = 1024);
    PROVIDE(_stack = ORIGIN(RAM) + LENGTH(RAM));
}
