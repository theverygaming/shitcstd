#include <sys/wait.h>
#include <abi-calls.h>

pid_t wait(int *wstatus) {
    return waitpid(-1, wstatus, 0);
}

pid_t waitpid(pid_t pid, int *wstatus, int options) {
    return ABI_WAITPID(pid, wstatus, options);
}
