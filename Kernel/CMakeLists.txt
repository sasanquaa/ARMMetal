set(KERNEL_SOURCES
    Main.cpp
    Kmalloc.h
    Uart.h
    Slab.h
    Slab.cpp
    Referable.h
    ReferableUtils.h
    ReferablePtr.h
    ReferablePtrForward.h
    UniquePtr.h
    UniquePtrForward.h)

add_library(Kernel ${KERNEL_SOURCES})
target_compile_options(
  Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-fno-exceptions -nodefaultlibs
                -c>)
target_link_options(Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nostartfiles
                    -ffreestanding>)
