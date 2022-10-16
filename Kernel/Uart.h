#pragma once

#include <stdint.h>

namespace Kernel {
namespace Uart {

static const double CPU_BASE_CLOCK = 24000000;
static const uint32_t DBAUD = CPU_BASE_CLOCK / (16 * 230400);
static const uint32_t IBAUD = DBAUD & 0x3f;
static const uint32_t FBAUD = (DBAUD >> 6) & 0xff;

static const uintptr_t UART0_BASE = 0x09000000;
static volatile uintptr_t* const UART0_DR = (volatile uintptr_t*)UART0_BASE;
static volatile uintptr_t* const UART0_FR = (volatile uintptr_t*)(UART0_BASE + 0x018);
static volatile uintptr_t* const UART0_CR = (volatile uintptr_t*)(UART0_BASE + 0x030);
static volatile uintptr_t* const UART0_IBRD = (volatile uintptr_t*)(UART0_BASE + 0x024);
static volatile uintptr_t* const UART0_FBRD = (volatile uintptr_t*)(UART0_BASE + 0x028);
static volatile uintptr_t* const UART0_LCRH = (volatile uintptr_t*)(UART0_BASE + 0x02C);

static constexpr uint16_t FR_BUSY = 1 << 3;
static constexpr uint16_t FR_TXFE = 1 << 7;
static constexpr uint16_t FR_TXFF = 1 << 5;
static constexpr uint16_t CR_UARTEN = 1;
static constexpr uint16_t LCRH_FEN = 1 << 4;
static constexpr uint16_t LCRH_WLEN = 3 << 5;

void wait()
{
    while ((*UART0_FR & FR_BUSY) != 0) { }
}

bool transmit_full()
{
    return (*UART0_FR & FR_TXFF) == 1;
}

void print(const char* s)
{
    wait();
    while (*s != '\0') {
        *UART0_DR = *s++;
        if (transmit_full()) {
            wait();
        }
    }
}

void println(const char* s)
{
    print(s);
    print("\n");
}

void setup()
{
    *UART0_LCRH = LCRH_FEN | LCRH_WLEN;
    *UART0_IBRD = IBAUD;
    *UART0_FBRD = *UART0_FBRD | FBAUD;
    *UART0_CR = CR_UARTEN;
}

}
}
