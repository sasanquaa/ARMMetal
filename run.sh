#/bin/bash

./build.sh &&
qemu-system-arm -nographic -M virt -kernel Build/Kernel/Main &&
clear &&
arm-none-eabi-objdump -Shsd Build/Kernel/Main
