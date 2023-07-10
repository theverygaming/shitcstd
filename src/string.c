#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int toupper(int c) {
    if (c >= 'a' && c <= 'z') {
        c -= 'a' - 'A';
    }
    return c;
}

int tolower(int c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }
    return c;
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

char *strncpy(char *destination, const char *source, size_t num) {
    char *destination_s = destination;
    bool copy = true;
    char c;
    for (size_t i = 0; i < num; i++) {
        if (copy) {
            c = *source++;
            if (c == '\0') {
                copy = false;
            }
        }
        *destination = c;
        destination++;
    }
    return destination_s;
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

const char *strrchr(const char *str, int character) {
    const char *ptr = 0;
    while (*str) {
        if (*str == character) {
            ptr = str;
        }
        str++;
    }
    return ptr;
}

char *strdup(const char *str1) {
    char *str2 = (char *)malloc(strlen(str1) + 1);
    strcpy(str2, str1);
    return str2;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *((const unsigned char *)str1) - *((const unsigned char *)str2);
}

int strncmp(const char *str1, const char *str2, size_t num) {
    size_t i;
    for (i = 0; (i < num) && *str1; i++) {
        if (*str1 != *str2) {
            return *((const unsigned char *)str1) - *((const unsigned char *)str2);
            break;
        }
        str1++;
        str2++;
    }
    if (i == num) {
        return 0;
    }
    return *((const unsigned char *)str1) - *((const unsigned char *)str2);
}
