#include <vix/syscall.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(__FUNNYARCH__)
void sys_exit(int rcode) {
    syscall(0, rcode, 0, 0, 0, 0, 0);
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    return syscall(1, fd, (vix_sysc_arg_t)buf, count, 0, 0, 0);
}

int sys_write(int fd, const void *buf, size_t count) {
    return syscall(2, fd, (vix_sysc_arg_t)buf, count, 0, 0, 0);
}
#else
#error "unsupported architecture"
#endif
