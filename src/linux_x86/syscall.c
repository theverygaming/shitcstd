#include <linux_x86/syscall.h>
#include <stdlib.h>

void sys_exit(int error_code) {
    syscall(1, (uint32_t)error_code, 0, 0, 0, 0, 0);
}

int sys_write(uint32_t fd, const char *buf, size_t count) {
    return syscall(4, fd, (uint32_t)buf, count, 0, 0, 0);
}

uint32_t sys_read(uint32_t fd, char *buf, size_t count) {
    return syscall(3, fd, (uint32_t)buf, count, 0, 0, 0);
}

void sys_waitpid(pid_t pid, int *start_addr, int options) {
    syscall(7, pid, (uint32_t)start_addr, options, 0, 0, 0);
}

pid_t sys_fork() {
    return syscall(2, 0, 0, 0, 0, 0, 0);
}

void sys_execve(const char *filename, char **argv, const char *const *envp) {
    syscall(11, (uint32_t)filename, (uint32_t)argv, (uint32_t)envp, 0, 0, 0);
}

int sys_chdir(const char *filename) {
    return syscall(12, (uint32_t)filename, 0, 0, 0, 0, 0);
}

void sys_time(time_t *tloc) {
    syscall(13, (uint32_t)tloc, 0, 0, 0, 0, 0);
}

int sys_sysinfo(struct sysinfo *info) {
    return syscall(116, (uint32_t)info, 0, 0, 0, 0, 0);
}

int sys_uname(struct utsname *buf) {
    return syscall(122, (uint32_t)buf, 0, 0, 0, 0, 0);
}

char *sys_getcwd(char *buf, size_t size) {
    return (char *)syscall(183, (uint32_t)buf, size, 0, 0, 0, 0);
}
