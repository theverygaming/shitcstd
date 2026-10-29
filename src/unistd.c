#include <abi-calls.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

pid_t fork() {
    return ABI_FORK();
}

unsigned int sleep(unsigned int seconds) { // TODO: use nanosleep syscall instead of this trash
    time_t start = time(NULL);
    while ((start + seconds) > time(NULL)) {}
    return 0;
}

char *getcwd(char *buf, size_t size) {
    ABI_GETCWD(buf, size);
    return buf;
}

int chdir(const char *path) {
    return ABI_CHDIR(path);
}

int execvp(const char *file, char *const argv[]) { // TODO: make it _the real_ exevp
    ABI_EXECVE(file, argv, NULL);
    return -1;
}

int execve(const char *path, char *const argv[], char *const envp[]) {
    ABI_EXECVE(path, argv, envp);
    return -1;
}

void *sbrk(intptr_t increment) {
    void *current = (void *)ABI_BRK(NULL);
    if (increment == 0) {
        return current;
    }
    void *new = ((char *)current) + increment;
    if ((void *)ABI_BRK(new) == current) {
        return (void *)-1;
    }
    return current;
}

int open(const char *path, int flags, mode_t mode) {
    return ABI_OPEN(path, flags, mode);
}

int close(int fd) {
    return ABI_CLOSE(fd);
}


ssize_t read(int fd, void *buf, size_t count) {
    return ABI_READ(fd, buf, count);
}

ssize_t write(int fd, const void *buf, size_t count) {
    return ABI_WRITE(fd, buf, count);
}

off_t lseek(int fd, off_t offset, int whence) {
    return ABI_LSEEK(fd, offset, whence);
}

