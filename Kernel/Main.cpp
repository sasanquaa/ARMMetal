#include <Kernel/Kmalloc.h>
#include <Kernel/ReferablePtr.h>
#include <Kernel/Uart.h>

class Foo : public Kernel::Referable {
public:
    char m_message[32] { 'W', 'e', ' ', 'g', 'o', 't', ' ', 'n', 'e', 'w', '!' };
};

extern "C" void start()
{
    Kernel::Uart::setup();
    Kernel::Uart::println("Kernel::Kmalloc::kmalloc_init()");
    Kernel::Kmalloc::kmalloc_init();
    Kernel::ReferablePtr<Foo> foo { new Foo(), true };
    Kernel::Uart::println(foo->m_message);
}
