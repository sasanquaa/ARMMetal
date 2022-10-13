ENTRY(_start)

MEMORY 
{
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    RAM (rwx) : ORIGIN = 0x40000000, LENGTH = 32M 
}

SECTIONS
{
    .text : { 
        *(.text*) 
        *(.rodata) 
        *(.init_array)
    } > ROM
    
    TEXT_END = .;

    .data : AT(ADDR(.text) + SIZEOF(.text)) { 
        DATA_START = .;
        *(.data) 
        . = ALIGN(8);
        DATA_END = .;
    } > RAM

    .bss : { 
        BSS_START = .;
        *(.bss) 
        BSS_END = .;
        . += 0x10000;
        STACK_TOP = .;
        . = ALIGN(8);
        HEAP_START = .;
        . += 0x10000;
        HEAP_END = .;
    } > RAM

}
