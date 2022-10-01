#include <stdint.h>

#define UART0_BASE_OFFSET 0x09000000

#define UART_BASE_CLOCK 24000000

#define UART_DR_OFFSET 0x000
#define UART_FR_OFFSET 0x018
#define UART_IBRD_OFFSET 0x024
#define UART_FBRD_OFFSET 0x028
#define UART_LCRH_OFFSET 0x02c
#define UART_CR_OFFSET 0x030
#define UART_IMSC_OFFSET 0x038
#define UART_DMACR_OFFSET 0x048

#define UART_FR_BUSY (1 << 3)

#define UART_CR_TXEN (1 << 8)
#define UART_CR_UARTEN (1 << 0)

#define UART_LCRH_FEN (1 << 4)

static volatile uint32_t* const UART0_BASE = (volatile uint32_t*)UART0_BASE_OFFSET;

volatile uint32_t* const reg_uart(const uint32_t offset)
{
    return (volatile uint32_t* const)(UART0_BASE + offset);
}

void wait_uart()
{
    while ((*reg_uart(UART_FR_OFFSET) & UART_FR_BUSY) != 0) { }
}

void print_uart(const char* s)
{
    wait_uart();
    while (*s != '\0') {
        *reg_uart(UART_DR_OFFSET) = *(s++);
        wait_uart();
    }
}

void setup_uart()
{
    const uint32_t cr = *reg_uart(UART_CR_OFFSET);
    const uint32_t lcrh = *reg_uart(UART_LCRH_OFFSET);
    const uint32_t dbaud = 4 * UART_BASE_CLOCK / 115200;
    const uint32_t ibaud = dbaud & 0x3f;
    const uint32_t fbaud = (dbaud >> 6) & 0xffff;

    *reg_uart(UART_CR_OFFSET) = cr & UART_CR_UARTEN;
    wait_uart();
    *reg_uart(UART_LCRH_OFFSET) = lcrh & ~UART_LCRH_FEN;
    *reg_uart(UART_IBRD_OFFSET) = ibaud;
    *reg_uart(UART_FBRD_OFFSET) = fbaud;
    *reg_uart(UART_IMSC_OFFSET) = 0x0;
    *reg_uart(UART_DMACR_OFFSET) = 0x0;
    *reg_uart(UART_CR_OFFSET) = UART_CR_TXEN | UART_CR_UARTEN;
}
