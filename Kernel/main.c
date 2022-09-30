#include <uart.c>

void start()
{
    setup_uart(UART0_BASE);
    print_uart(UART0_BASE, "Hello, World!\n");
}
