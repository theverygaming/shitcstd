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

void *memcpy(void *dest, const void *src, size_t n) {
    char *dest2 = (char *)dest;
    char *src2 = (char *)src;
    while (n--)
        *dest2++ = *src2++;
    return dest;
}

void *memset(void *ptr, int value, size_t num) {
    char *dest = (char *)ptr;
    while (num--)
        *dest++ = value;
    return dest;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
    uint8_t *c1 = (uint8_t *)ptr1;
    uint8_t *c2 = (uint8_t *)ptr2;
    while (num--) {
        if (*c1++ != *c2++) {
            return c1[-1] < c2[-1] ? -1 : 1;
        }
    }
    return 0;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *((const unsigned char *)str1) - *((const unsigned char *)str2);
}

size_t strlen(const char *str) {
    const char *str2 = str;
    while (*str2) {
        str2++;
    }
    return (str2 - str);
}

char *strchr(char *str, int character) {
    while (*str) {
        if (*str == character) {
            return str;
        }
        str++;
    }
    if (*str == character) {
        return str;
    }
    return 0;
}

size_t strcspn(const char *s1, const char *s2) {
    size_t n = 0;
    if (*s2 == 0) {
        return 0;
    }
    while (*s1) {
        if (strchr((char *)s2, *s1)) {
            return n;
        }
        s1++;
        n++;
    }
    return n;
}

const char *strstr(const char *str1, const char *str2) {
    size_t str2len = strlen(str2);
    while (*str1) {
        if (!memcmp(str1++, str2, str2len)) {
            return str1 - 1;
        }
    }
    return 0;
}

char *strcpy(char *destination, const char *source) {
    size_t len = strlen(source);
    memcpy(destination, source, len + 1);
    return destination;
}

char *strsep(char **restrict stringp, const char *restrict delim) {
    if (*stringp == NULL) {
        return NULL;
    }

    char *oldstart = *stringp;

    char *newend = *stringp + strcspn(*stringp, delim);

    if (*newend != '\0') {
        *newend++ = '\0';
    } else {
        newend = NULL;
    }

    *stringp = newend;
    return oldstart;
}

size_t sscanf(const char *str, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    size_t instrcnt = 0;
    size_t items_filled = 0;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 's': {
                char fmtcut[100];
                size_t cspn = strcspn(fmt + 1, "%");
                if (cspn >= 100) {
                    return items_filled;
                }
                memcpy(fmtcut, fmt + 1, cspn);
                fmtcut[cspn] = '\0';

                size_t cpcnt = (size_t)strstr(&str[instrcnt], fmtcut);
                if (!cpcnt) {
                    return items_filled;
                }
                cpcnt -= (size_t)&str[instrcnt];
                char *arg = va_arg(args, char *);
                memcpy((void *)arg, (void *)&str[instrcnt], cpcnt);
                instrcnt += cpcnt - 1;

                items_filled++;
                break;
            }
            }
        }
        instrcnt++;
        fmt++;
    }

    va_end(args);
    return items_filled;
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

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    size_t chars_written = 0;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case '%': {
                fmt += 1;
                sys_write(1, "%", 1);
                break;
            }
            case 's': {
                fmt += 1;
                char *arg = va_arg(args, char *);
                sys_write(1, arg, strlen(arg));
                chars_written += strlen(arg);
                break;
            }
            case 'u': {
                fmt += 1;
                size_t arg = va_arg(args, size_t);
                char buf[11];
                char *ret = itoa(arg, buf, 10);
                sys_write(1, ret, strlen(ret));
                chars_written += strlen(ret);
                break;
            }
            }
        }
        int count = strcspn(fmt, "%");
        sys_write(1, fmt, count);
        chars_written += count;
        fmt += count;
    }

    va_end(args);
    return chars_written;
}

int getchar() {
    char buf;
    sys_read(STDIN_FILENO, &buf, 1);
    return (int)buf;
}

void perror(const char *s) {
    if (s != NULL) {
        printf("%s: \n", s);
    }
}

double sin(double x) {
    float xf = (float)x;
    float *xfp = &xf;
    asm volatile("flds (%0)\n\t" // load into ST(0)
                 "fsin\n\t"
                 "fstps (%1)\n\t" // pop off ST(0)
                 : "=r"(xfp)
                 : "r"(xfp));
    return (double)xf;
}

double cos(double x) {
    float xf = (float)x;
    float *xfp = &xf;
    asm volatile("flds (%0)\n\t" // load into ST(0)
                 "fcos\n\t"
                 "fstps (%1)\n\t" // pop off ST(0)
                 : "=r"(xfp)
                 : "r"(xfp));
    return (double)xf;
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
