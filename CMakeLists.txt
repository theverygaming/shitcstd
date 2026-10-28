cmake_minimum_required(VERSION 3.7)

# prevents cmake from exploding with fucky compilers (e.g. ones that default to -lc even though there's no C stdlib)
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(shitcstd)

set(CMAKE_C_STANDARD 99)
enable_language(ASM)

add_compile_options(-fno-builtin -fno-stack-protector -nostdinc -nostdlib)

set(ABIS "linux")
if(NOT ABI IN_LIST ABIS)
    message(FATAL_ERROR "unsupported ABI '${ABI}', supported ABIs: ${ABIS}")
endif()

include_directories(BEFORE SYSTEM include "abi/${ABI}/include")

file(GLOB_RECURSE SOURCES "src/*.c")

file(GLOB_RECURSE ABI_SOURCES
    "abi/${ABI}/src/*.c"
    "abi/${ABI}/src/*.S")

add_library(shitcstd STATIC ${SOURCES} ${ABI_SOURCES})

target_compile_options(shitcstd PRIVATE -Wall -Wextra)

set(CMAKE_INSTALL_PREFIX /usr CACHE PATH "Set cmake Default to /usr" FORCE)

install(TARGETS shitcstd DESTINATION lib)
