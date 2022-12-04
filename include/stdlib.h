#pragma once
#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
void exit(int status);

unsigned long int strtoul(const char *str, char **endptr, int base);

#define RAND_MAX 32767
int rand();
void srand(unsigned int seed);
