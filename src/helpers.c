#include "helpers.h"
#include <stdint.h>
#include <stdbool.h>

int shitcstd_atoi_sized(const char *str, size_t n) {
    int num = 0;
    bool negative = false;
    while (n && *str) {
        if (*str == '-' && num == 0) {
            str++;
            n--;
            negative = true;
            continue;
        }
        if (*str < '0' || *str > '9') {
            break;
        }
        uint8_t current_num = *str - '0';
        num = (num * 10) + current_num;
        str++;
        n--;
    }
    if (negative) {
        num = -num;
    }
    return num;
}
