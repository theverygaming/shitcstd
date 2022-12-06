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
