#pragma once
#include <stdint.h>
#include <sys/types.h>

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

pid_t fork();

unsigned int sleep(unsigned int seconds);

char *getcwd(char *buf, size_t size);
int chdir(const char *path);
int execvp(const char *file, char *const argv[]);
void *sbrk(intptr_t increment);
int execve(const char *path, char *const argv[], char *const envp[]);

int open(const char *path, int flags, mode_t mode);
int close(int fd);

ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
