#include <sys/wait.h>
#include <linux/syscall.h>

pid_t wait(int *wstatus) {
    return waitpid(-1, wstatus, 0);
}

pid_t waitpid(pid_t pid, int *wstatus, int options) {
    return sys_waitpid(pid, wstatus, options);
}
