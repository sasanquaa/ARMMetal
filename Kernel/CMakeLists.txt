set(KERNEL_SOURCES
    Main.cpp
    Kmalloc.h
    Uart.h
    Slab.h
    Slab.cpp
    Referable.h
    ReferableUtils.h
    Traits.h
    ReferablePtr.h
    WeakPtr.h
    WeaklyReferable.h
    UniquePtr.h)

add_library(Kernel ${KERNEL_SOURCES})
target_compile_options(
  Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-fno-exceptions -fno-rtti
                -nodefaultlibs -c>)
target_link_options(Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nostartfiles
                    -ffreestanding>)
