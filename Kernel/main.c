#include <uart.c>

void start()
{
    setup_uart();
    print_uart("Hello, World!\n");
}
