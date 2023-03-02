cmake_minimum_required(VERSION 3.1)
project(shitcstd)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_compile_options(-fno-builtin -fno-stack-protector -nostdinc)

include_directories(BEFORE SYSTEM include)

list(APPEND SOURCES
    src/arith64.c
    src/string.c
    src/strings.c
    src/stdio.c
    src/unistd.c
    src/malloc.c
    src/math.c
    src/stdlib.c
    src/time.c
    src/sys/wait.c
    src/linux_x86/syscall.c
    src/linux_x86/syscall_asm.S
    src/linux_x86/crt0.S)

add_library(shitcstd STATIC ${SOURCES})
set_target_properties(shitcstd PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

set(CMAKE_INSTALL_PREFIX /usr CACHE PATH "Set cmake Default to /usr" FORCE)

install(TARGETS shitcstd DESTINATION lib)
