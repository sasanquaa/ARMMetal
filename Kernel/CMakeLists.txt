set(KERNEL_SOURCES Main.cpp Kmalloc.h Uart.h Slab.h Slab.cpp)

add_library(Kernel ${KERNEL_SOURCES})
target_include_directories(Kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(
  Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-fno-exceptions -nodefaultlibs
                -c>)
target_link_options(Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nostartfiles
                    -ffreestanding>)
