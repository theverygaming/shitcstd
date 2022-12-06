#include <linux_x86/syscall.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void exit(int status) {
    sys_exit(status);
    printf("OS skill issues\n");
    while (true) {}
}

char *itoa(size_t value, char *str, size_t base) {
    char *ptr = str;

    do {
        size_t mod = value % base;
        unsigned char start = '0';
        if ((base == 16) && (mod > 9)) {
            start = 'a';
            mod -= 10;
        }
        *ptr++ = start + mod;
    } while ((value /= base) > 0);
    *ptr = '\0';

    size_t len = strlen(str);

    for (int i = 0; i < len / 2; i++) {
        char c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }

    return str;
}

char *itoa_signed(ssize_t value, char *str, size_t base) {
    bool sign = false;
    if(value < 0) {
        sign = true;
        value = -value;
    }
    
    char *ptr = str;

    int dig = 0;
    do {
        size_t mod = value % base;
        unsigned char start = '0';
        if ((base == 16) && (mod > 9)) {
            start = 'a';
            mod -= 10;
        }
        *ptr++ = start + mod;
    } while ((value /= base) > 0);
    if(sign) {
        *ptr++ = '-';
    }
    *ptr = '\0';

    size_t len = strlen(str);

    for (int i = 0; i < len / 2; i++) {
        char c = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = c;
    }

    return str;
}

int atoi(const char *str) {
    int num = 0;
    bool negative = false;
    while (*str) {
        if (*str == '-' && num == 0) {
            str++;
            negative = true;
            continue;
        }
        if (*str < '0' || *str > '9') {
            break;
        }
        uint8_t current_num = *str - '0';
        num = (num * 10) + current_num;
        str++;
    }
    if (negative) {
        num = -num;
    }
    return num;
}

unsigned long int strtoul(const char *str, char **endptr, int base) {
    unsigned long int num = 0;
    while (*str) {
        if (*str < '0' || *str > '9') {
            break;
        }
        uint8_t current_num = *str - '0';
        num = (num * base) + current_num;
        str++;
    }
    if (endptr != NULL) {
        *endptr = (char *)str;
    }
    return num;
}

static int rand_seed = 1;

int rand() {
    rand_seed = (42069 * rand_seed + 1) % (RAND_MAX + 1);
    if (rand_seed < 0) { // make sure the result is always positive
        rand_seed = -rand_seed;
    }
    return rand_seed;
}

void srand(unsigned int seed) {
    rand_seed = seed + 621;
}
