.globl _start

_start:
    ldr x0, =STACK_START
    mov sp, x0

    ldr x0, =TEXT_END
    ldr x1, =DATA_START
    ldr x2, =DATA_END

boot_reset_loop_data:
    cmp x1, x2
    bge boot_reset_loop_data_end
    ldr x3, [x0], #8
    str x3, [x1], #8
    blt boot_reset_loop_data

boot_reset_loop_data_end:
    ldr x1, =RODATA_START
    ldr x2, =RODATA_END

boot_reset_loop_rodata:
    cmp x1, x2
    bge boot_reset_loop_rodata_end
    ldr x3, [x0], #8
    str x3, [x1], #8
    blt boot_reset_loop_rodata

boot_reset_loop_rodata_end:
    ldr x1, =BSS_START
    ldr x2, =BSS_END

boot_reset_loop_bss:
    cmp x1, x2
    bge boot_reset_loop_bss_end
    ldr x3, [x0], #8
    str x3, [x1], #8
    blt boot_reset_loop_bss

boot_reset_loop_bss_end:
    bl start
    b .

.balign 8
exception_table:
exception_el0_sync:
    b .

.balign 0x80
exception_el0_irq:
    b .

.balign 0x80
exception_el0_fiq:
    b .

.balign 0x80
exception_el0_serror:
    b .

.balign 0x80
exception_elx_sync:
    b .

.balign 0x80
exception_elx_irq:
    b .

.balign 0x80
exception_elx_fiq:
    b .

.balign 0x80
exception_elx_serror:
    b .

.balign 0x80
exception_ell_sync_aarch64:
    b .

.balign 0x80
exception_ell_irq_aarch64:
    b .

.balign 0x80
exception_ell_fiq_aarch64:
    b .

.balign 0x80
exception_ell_serror_aarch64:
    b .

.balign 0x80
exception_ell_sync_aarch32:
    b .

.balign 0x80
exception_ell_irq_aarch32:
    b .

.balign 0x80
exception_ell_fiq_aarch32:
    b .

.balign 0x80
exception_ell_serror_aarch32:
    b .

.balign 0x4000
translation_table_el1:

