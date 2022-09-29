#include <stdint.h>

#define UART0_BASE_OFFSET 0x09000000

#define UART_DR_OFFSET 0x000

static volatile uint32_t* const UART0_BASE = (volatile uint32_t*)UART0_BASE_OFFSET;

volatile uint32_t* const reg_uart(const volatile uint32_t* const uart, const uint32_t offset)
{
    return (volatile uint32_t* const)(uart + offset);
}

void print_uart(volatile uint32_t* const uart, const char* s)
{
    while (*s != '\0') {
        *reg_uart(uart, UART_DR_OFFSET) = *(s++);
    }
}

void start()
{
    print_uart(UART0_BASE, "Hello, World!\n");
}
