#define MODE_FIQ #0x11

.globl _start

_start:
    b boot_reset
    b .
    b .
    b .
    b .
    b .
    b .

boot_reset:
    mov r0, MODE_FIQ
    msr cpsr_c, r0

    ldr sp, =STACK_START
    ldr r0, =TEXT_END
    ldr r1, =DATA_START
    ldr r2, =DATA_END

boot_reset_loop_data:
    cmp r1, r2
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt boot_reset_loop_data

    ldr r1, =RODATA_START
    ldr r2, =RODATA_END

boot_reset_loop_rodata:
    cmp r1, r2
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt boot_reset_loop_rodata

    ldr r1, =BSS_START
    ldr r2, =BSS_END

boot_reset_loop_bss:
    cmp r1, r2
    ldrlt r3, [r0], #4
    strlt r3, [r1], #4
    blt boot_reset_loop_bss

    bl start
    b .

