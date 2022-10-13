add_executable(Main boot.S)
target_link_libraries(Main PRIVATE Kernel)
target_link_options(Main PRIVATE $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-T
                    ${CMAKE_CURRENT_SOURCE_DIR}/link.ld>)
