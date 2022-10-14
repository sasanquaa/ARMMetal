ENTRY(_start)

MEMORY 
{
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 1M
    RAM (rwx) : ORIGIN = 0x40000000, LENGTH = 127M 
}

SECTIONS
{
    .text : { 
        *(.text*) 
        . = ALIGN(8);
        TEXT_END = .;
    } > ROM

    .data : AT(ADDR(.text) + SIZEOF(.text)) { 
        DATA_START = .;
        *(.data) 
        . = ALIGN(8);
        DATA_END = .;
    } > RAM

    .rodata : {
        RODATA_START = .;
        *(.rodata)
        . = ALIGN(8);
        RODATA_END = .;
    } > RAM

    .bss : { 
        BSS_START = .;
        *(.bss) 
        . = ALIGN(8);
        BSS_END = .;
    } > RAM

    HEAP_START = .;

    STACK_START = ALIGN(ORIGIN(RAM) + LENGTH(RAM));

    /DISCARD/ : {
        *(.init_array)
    }

}
