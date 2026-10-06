cmake_minimum_required(VERSION 3.7)

# prevents cmake from exploding with fucky compilers (e.g. ones that default to -lc even though there's no C stdlib)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(shitcstd)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_compile_options(-fno-builtin -fno-stack-protector -nostdinc -nostdlib)

include_directories(BEFORE SYSTEM include)

list(APPEND SOURCES
    src/errno.c
    src/string.c
    src/strings.c
    src/stdio.c
    src/unistd.c
    src/malloc.c
    src/math.c
    src/stdlib.c
    src/time.c
    src/sys/wait.c
    src/linux/syscall.c
    src/linux/syscall_asm.S
    src/linux/crt0.S)

add_library(shitcstd STATIC ${SOURCES})

target_compile_options(shitcstd PRIVATE -Wall -Wextra)

set(CMAKE_INSTALL_PREFIX /usr CACHE PATH "Set cmake Default to /usr" FORCE)

install(TARGETS shitcstd DESTINATION lib)
