#include <sys/wait.h>
#include <linux/syscall.h>

pid_t wait(int *wstatus) {
    return sys_waitpid(-1, wstatus, 0);
}
