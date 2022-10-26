#include <linux_x86/syscall.h>
#include <stddef.h>
#include <time.h>
#include <unistd.h>

pid_t fork() {
    return sys_fork();
}

unsigned int sleep(unsigned int seconds) { // TODO: use nanosleep syscall instead of this trash
    time_t start = time(NULL);
    while ((start + seconds) > time(NULL)) {}
    return 0;
}

char *getcwd(char *buf, size_t size) {
    sys_getcwd(buf, size);
    return buf;
}

int chdir(const char *path) {
    return sys_chdir(path);
}

int execvp(const char *file, char *const argv[]) { // TODO: make it _the real_ exevp
    sys_execve(file, argv, NULL);
    return -1;
}
