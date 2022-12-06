#pragma once
#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *ptr, int value, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);

size_t strlen(const char *str);
char *strchr(char *str, int character);
size_t strcspn(const char *str1, const char *str2);
const char *strstr(const char *str1, const char *str2);
char *strcpy(char *destination, const char *source);
char *strncpy(char *destination, const char *source, size_t num);
char *strsep(char **restrict stringp, const char *restrict delim);

const char *strrchr(const char *str, int character);

char *strdup(const char *str1);

int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t num);
