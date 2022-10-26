#include <time.h>
#include <stddef.h>
#include <linux_x86/syscall.h>

time_t time(time_t *arg) {
    time_t current_time;
    sys_time(&current_time);
    if(arg != NULL) {
        *arg = current_time;
    }
    return current_time;
}
