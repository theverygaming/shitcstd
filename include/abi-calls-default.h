#pragma once

static int abi_default_do_nothing() {
    return -1;
}

#define ABI_EXIT(code) abi_default_do_nothing()
#define ABI_TIME(tptr) abi_default_do_nothing()
#define ABI_UNAME(utsnameptr) abi_default_do_nothing()

#define ABI_OPEN(path, flags, mode) abi_default_do_nothing()
#define ABI_CLOSE(fd) abi_default_do_nothing()
#define ABI_READ(fd, buf, count) abi_default_do_nothing()
#define ABI_WRITE(fd, buf, count) abi_default_do_nothing()
#define ABI_LSEEK(fd, offset, whence) abi_default_do_nothing()

#define ABI_WAITPID(pid, wstatus, options) abi_default_do_nothing()
#define ABI_FORK() abi_default_do_nothing()
#define ABI_GETCWD(buf, size) abi_default_do_nothing()
#define ABI_CHDIR(path) abi_default_do_nothing()
#define ABI_EXECVE(path, argv, envp) abi_default_do_nothing()
#define ABI_BRK(newaddr) abi_default_do_nothing()
