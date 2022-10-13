#/bin/bash

./build.sh &&
qemu-system-arm -nographic -M virt -kernel Build/Boot/Main &&
clear &&
arm-none-eabi-objdump -Shsd Build/Boot/Main
