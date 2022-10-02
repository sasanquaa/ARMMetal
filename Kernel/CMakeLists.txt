set(KERNEL_SOURCES 
    main.c 
    uart.c 
)

add_library(Kernel ${KERNEL_SOURCES})
target_include_directories(Kernel PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(Main boot.S)
target_link_libraries(Main PRIVATE Kernel)
target_compile_options(Main PRIVATE
    $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nodefaultlibs -c>
)
target_link_options(Main PRIVATE 
    $<$<COMPILE_LANGUAGE:ASM>:-nostartfiles -ffreestanding -T ${CMAKE_CURRENT_SOURCE_DIR}/link.ld>
)
