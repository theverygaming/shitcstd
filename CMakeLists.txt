cmake_minimum_required(VERSION 3.1)
project(shitcstd)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_compile_options(-fno-builtin -fno-stack-protector -nostdinc)

include_directories(BEFORE SYSTEM include)

list(APPEND SOURCES 
    src/stdlib.c
    src/time.c
    src/unistd.c
    src/sys/wait.c
    src/linux_x86/syscall.c
    src/linux_x86/syscall_asm.S
    src/linux_x86/crt0.S)

add_library(shitcstd STATIC ${SOURCES})
set_target_properties(shitcstd PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
