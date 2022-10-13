#include <Kmalloc.cpp>
#include <Uart.h>

static const Kernel::Uart UART;

extern "C" void start()
{
    Kernel::kmalloc_init();
}
