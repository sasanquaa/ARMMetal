#include <Uart.h>

extern "C" void start()
{
    Kernel::Uart uart;
    uart.print("Hello, World!");
}
