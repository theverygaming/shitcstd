#include <linux/syscall.h>
#include <stdlib.h>
#include <sys/types.h>

#if defined(__i386__)

void sys_exit(int error_code) {
    syscall(1, (uint32_t)error_code, 0, 0, 0, 0, 0);
}

pid_t sys_fork() {
    return syscall(2, 0, 0, 0, 0, 0, 0);
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    return syscall(3, fd, (linux_sysc_arg_t)buf, count, 0, 0, 0);
}

int sys_write(int fd, const void *buf, size_t count) {
    return syscall(4, fd, (linux_sysc_arg_t)buf, count, 0, 0, 0);
}

int sys_open(const char *filename, int flags, umode_t mode) {
    return syscall(5, (linux_sysc_arg_t)filename, flags, mode, 0, 0, 0);
}

int sys_close(unsigned int fd) {
    return syscall(6, fd, 0, 0, 0, 0, 0);
}

pid_t sys_waitpid(pid_t pid, int *start_addr, int options) {
    return syscall(7, pid, (linux_sysc_arg_t)start_addr, options, 0, 0, 0);
}

void sys_execve(const char *filename, char *const *argv, char *const *envp) {
    syscall(11, (linux_sysc_arg_t)filename, (linux_sysc_arg_t)argv, (linux_sysc_arg_t)envp, 0, 0, 0);
}

int sys_chdir(const char *filename) {
    return syscall(12, (linux_sysc_arg_t)filename, 0, 0, 0, 0, 0);
}

void sys_time(time_t *tloc) {
    syscall(13, (linux_sysc_arg_t)tloc, 0, 0, 0, 0, 0);
}

off_t sys_lseek(unsigned int fd, off_t offset, unsigned int whence) {
    return syscall(19, fd, offset, whence, 0, 0, 0);
}

int sys_brk(void *addr) {
    return syscall(45, (unsigned long)addr, 0, 0, 0, 0, 0);
}

int sys_sysinfo(struct sysinfo *info) {
    return syscall(116, (linux_sysc_arg_t)info, 0, 0, 0, 0, 0);
}

int sys_uname(struct linux_utsname *buf) {
    return syscall(122, (linux_sysc_arg_t)buf, 0, 0, 0, 0, 0);
}

char *sys_getcwd(char *buf, size_t size) {
    return (char *)syscall(183, (linux_sysc_arg_t)buf, size, 0, 0, 0, 0);
}
#elif defined(__x86_64__)

void sys_exit(int error_code) {
    syscall(60, (uint32_t)error_code, 0, 0, 0, 0, 0);
}

pid_t sys_fork() {
    return syscall(57, 0, 0, 0, 0, 0, 0);
}

ssize_t sys_read(int fd, void *buf, size_t count) {
    return syscall(0, fd, (linux_sysc_arg_t)buf, count, 0, 0, 0);
}

int sys_write(int fd, const void *buf, size_t count) {
    return syscall(1, fd, (linux_sysc_arg_t)buf, count, 0, 0, 0);
}

int sys_open(const char *filename, int flags, umode_t mode) {
    return syscall(2, (linux_sysc_arg_t)filename, flags, mode, 0, 0, 0);
}

int sys_close(unsigned int fd) {
    return syscall(3, fd, 0, 0, 0, 0, 0);
}

pid_t sys_waitpid(pid_t pid, int *start_addr, int options) {
    // this is actually wait4 but with these args it's equivalent
    return syscall(61, pid, (linux_sysc_arg_t)start_addr, options, 0, 0, 0);
}

void sys_execve(const char *filename, char *const *argv, char *const *envp) {
    syscall(59, (linux_sysc_arg_t)filename, (linux_sysc_arg_t)argv, (linux_sysc_arg_t)envp, 0, 0, 0);
}

int sys_chdir(const char *filename) {
    return syscall(80, (linux_sysc_arg_t)filename, 0, 0, 0, 0, 0);
}

void sys_time(time_t *tloc) {
    syscall(201, (linux_sysc_arg_t)tloc, 0, 0, 0, 0, 0);
}

off_t sys_lseek(unsigned int fd, off_t offset, unsigned int whence) {
    return syscall(8, fd, offset, whence, 0, 0, 0);
}

int sys_brk(void *addr) {
    return syscall(12, (unsigned long)addr, 0, 0, 0, 0, 0);
}

int sys_sysinfo(struct sysinfo *info) {
    return syscall(99, (linux_sysc_arg_t)info, 0, 0, 0, 0, 0);
}

int sys_uname(struct linux_utsname *buf) {
    // FIXME: this is actually newuname which has a different struct...
    return syscall(63, (linux_sysc_arg_t)buf, 0, 0, 0, 0, 0);
}

char *sys_getcwd(char *buf, size_t size) {
    return (char *)syscall(79, (linux_sysc_arg_t)buf, size, 0, 0, 0, 0);
}
#else
#error "unsupported architecture"
#endif

