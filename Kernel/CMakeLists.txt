set(KERNEL_SOURCES main.cpp Uart.h Uart.cpp)

add_library(Kernel ${KERNEL_SOURCES})
target_include_directories(Kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_options(
  Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-fno-exceptions -nodefaultlibs
                -c>)
target_link_options(Kernel PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nostartfiles
                    -ffreestanding>)

add_executable(Main boot.S)
target_link_libraries(Main PRIVATE Kernel)
target_link_options(Main PRIVATE $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-T
                    ${CMAKE_CURRENT_SOURCE_DIR}/link.ld>)
