#include <time.h>
#include <stddef.h>
#include <abi-calls.h>

time_t time(time_t *arg) {
    time_t current_time;
    ABI_TIME(&current_time);
    if(arg != NULL) {
        *arg = current_time;
    }
    return current_time;
}
