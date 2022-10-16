set(LIBC_SOURCES
    assert.h
    assert.cpp
    complex.h
    ctype.h
    errno.h
    fenv.h
    float.h
    inttypes.h
    iso646.h
    limits.h
    locale.h
    math.h
    math.cpp
    setjmp.h
    signal.h
    stdalign.h
    stdarg.h
    stdatomic.h
    stdbool.h
    stdint.h
    stdio.h
    stdio.cpp
    stdlib.h
    stdlib.cpp
    stdnoreturn.h
    string.h
    tgmath.h
    threads.h
    time.h
    uchar.h
    wchar.h
    wctype.h)

add_library(LibC ${LIBC_SOURCES})
target_compile_options(
  LibC PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-fno-exceptions -nodefaultlibs
              -c>)
target_link_options(LibC PUBLIC $<$<COMPILE_LANGUAGE:C,CXX,ASM>:-nostartfiles
                    -ffreestanding>)
