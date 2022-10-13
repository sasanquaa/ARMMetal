#include <Kmalloc.h>
#include <Uart.h>

extern "C" void start()
{
    Kernel::Uart::setup();
    Kernel::Uart::println("Kernel::Kmalloc::kmalloc_init()");
    Kernel::Kmalloc::kmalloc_init();
    char* message = new char[32] { 'W', 'e', ' ', 'g', 'o', 't', ' ', 'n', 'e', 'w', '!' };
    Kernel::Uart::println(message);
}
