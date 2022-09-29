#!/bin/bash

arm-none-eabi-gcc -c boot.S main.c &&
arm-none-eabi-ld -T link.ld &&
qemu-system-arm -nographic -M virt -kernel main.elf &&
clear &&
arm-none-eabi-objdump -Shsd main.elf &&
rm boot.o main.o main.elf

