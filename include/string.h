#pragma once
#include <stdint.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *ptr, int value, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);

int strcmp(const char *str1, const char *str2);
size_t strlen(const char *str);
char *strchr(char *str, int character);
size_t strcspn(const char *str1, const char *str2);
const char *strstr(const char *str1, const char *str2);
