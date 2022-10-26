#pragma once
#include <stdint.h>

void exit(int status);

#define RAND_MAX 32767
int rand();
void srand(unsigned int seed);
