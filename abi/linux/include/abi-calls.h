#pragma once
#include <abi-calls-default.h>
#include <abi-defs.h>
#include <linux/syscall.h>

#undef ABI_EXIT
#define ABI_EXIT(code) sys_exit(code)
#undef ABI_TIME
#define ABI_TIME(tptr) sys_time(tptr)
#undef ABI_UNAME
#define ABI_UNAME(utsnameptr) sys_uname((struct linux_utsname *)(utsnameptr))

#undef ABI_OPEN
#define ABI_OPEN(path, flags, mode) sys_open(path, flags, mode)
#undef ABI_CLOSE
#define ABI_CLOSE(fd) sys_close(fd)
#undef ABI_READ
#define ABI_READ(fd, buf, count) sys_read(fd, buf, count)
#undef ABI_WRITE
#define ABI_WRITE(fd, buf, count) sys_write(fd, buf, count)
#undef ABI_LSEEK
#define ABI_LSEEK(fd, offset, whence) sys_lseek(fd, offset, whence)

#undef ABI_WAITPID
#define ABI_WAITPID(pid, wstatus, options) sys_waitpid(pid, wstatus, options)
#undef ABI_FORK
#define ABI_FORK() sys_fork()
#undef ABI_GETCWD
#define ABI_GETCWD(buf, size) sys_getcwd(buf, size)
#undef ABI_CHDIR
#define ABI_CHDIR(path) sys_chdir(path)
#undef ABI_EXECVE
#define ABI_EXECVE(path, argv, envp) sys_execve(path, argv, envp)
#undef ABI_BRK
#define ABI_BRK(newaddr) sys_brk(newaddr)
