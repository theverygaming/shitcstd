#include <sys/wait.h>
#include <linux_x86/syscall.h>

pid_t wait(int *wstatus) {
    sys_waitpid(-1, wstatus, 0);
}
