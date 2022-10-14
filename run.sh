#/bin/bash

./build.sh &&
qemu-system-aarch64 -nographic -M virt -cpu cortex-a72 -kernel Build/Boot/Main &&
clear &&
/opt/gcc-aarch64-none-elf/bin/aarch64-none-elf-objdump -Shsd Build/Boot/Main
