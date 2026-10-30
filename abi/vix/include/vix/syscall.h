#pragma once
#include <stddef.h>
#include <sys/types.h>
#include <time.h>

#if defined(__FUNNYARCH__)
typedef uint32_t vix_sysc_arg_t;
#else
#error "unsupported architecture"
#endif

extern vix_sysc_arg_t syscall(vix_sysc_arg_t syscall_num, vix_sysc_arg_t a1, vix_sysc_arg_t a2, vix_sysc_arg_t a3, vix_sysc_arg_t a4, vix_sysc_arg_t a5, vix_sysc_arg_t a6);

void sys_exit(int rcode);
ssize_t sys_read(int fd, void *buf, size_t count);
int sys_write(int fd, const void *buf, size_t count);
