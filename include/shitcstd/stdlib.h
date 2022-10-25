#pragma once
#include <shitcstd/stdint.h>

void exit(int status);
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *ptr, int value, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
char *strchr(char *str, int character);
size_t strcspn(const char *str1, const char *str2);
const char *strstr(const char *str1, const char *str2);

#define va_list __builtin_va_list
#define va_start(v, l) __builtin_va_start((v), (l))
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end

size_t sscanf(const char *str, const char *fmt, ...);
int printf(const char *fmt, ...);

/* math */
double sin(double x);
double cos(double x);

/* other  */
#define RAND_MAX 32767
int rand();
void srand(unsigned int seed);
