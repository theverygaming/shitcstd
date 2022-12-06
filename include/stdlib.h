#pragma once
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void exit(int status);

unsigned long int strtoul(const char *str, char **endptr, int base);

#define RAND_MAX 32767
int rand();
void srand(unsigned int seed);

char *itoa(size_t value, char *str, size_t base);
char *itoa_signed(ssize_t value, char *str, size_t base);
int atoi(const char *str);

int abs(int n);

void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void free(void *ptr);

void *calloc(size_t num, size_t size);
