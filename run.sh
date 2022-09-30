#/bin/bash

./build.sh &&
qemu-system-arm -nographic -M virt -kernel build/Kernel/Main &&
clear &&
arm-none-eabi-objdump -Shsd build/Kernel/Main
