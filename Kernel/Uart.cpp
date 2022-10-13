#include <Uart.h>

namespace Kernel {

static volatile uint32_t* const UART0_BASE = (volatile uint32_t*)0x09000000;

static constexpr uint32_t CPU_BASE_CLOCK = 24000000;

static constexpr uint32_t UART_FR_BUSY = 1 << 3;
static constexpr uint32_t UART_CR_TXEN = 1 << 8;
static constexpr uint32_t UART_CR_UARTEN = 1 << 0;
static constexpr uint32_t UART_LCRH_FEN = 1 << 4;

class Register {
public:
    enum class Type {
        DR = 0x000,
        FR = 0x018,
        IBRD = 0x024,
        FBRD = 0x028,
        LCRH = 0x02c,
        CR = 0x030,
        IMSC = 0x038,
        DMAC = 0x048
    };

    Register(volatile uint32_t* base, const Type& type)
        : m_ptr(base + (volatile uint32_t)type)
    {
    }

    void write(uint32_t value)
    {
        *m_ptr = value;
    }

    uint32_t read()
    {
        return *m_ptr;
    }

    volatile uint32_t* m_ptr;
};

Register reg(const Kernel::Register::Type& type)
{
    return Register(UART0_BASE, type);
}

void Uart::print(const char* s) const
{
    Register dr = reg(Register::Type::DR);
    wait();
    while (*s != '\0') {
        dr.write(*s++);
        wait();
    }
}

void Uart::setup() const
{
    Register cr = reg(Register::Type::CR);
    Register lcrh = reg(Register::Type::LCRH);
    Register ibrd = reg(Register::Type::IBRD);
    Register fbrd = reg(Register::Type::FBRD);
    Register imsc = reg(Register::Type::IMSC);

    uint32_t dbaud = 4 * CPU_BASE_CLOCK / 115200;
    uint32_t ibaud = dbaud & 0x3f;
    uint32_t fbaud = (dbaud >> 6) & 0xffff;

    cr.write(cr.read() & UART_CR_UARTEN);
    wait();
    lcrh.write(lcrh.read() & ~UART_LCRH_FEN);
    ibrd.write(ibaud);
    fbrd.write(fbaud);
    imsc.write(0);
    cr.write(UART_CR_TXEN | UART_CR_UARTEN);
}

void Uart::wait() const
{
    Register fr = reg(Register::Type::FR);
    while ((fr.read() & UART_FR_BUSY) != 0) { }
}

}
