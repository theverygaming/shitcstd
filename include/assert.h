#pragma once
#include <stdlib.h>
#include <stdio.h>
#ifndef NDEBUG
#define assert(condition) do { if(!(condition)) { printf("assertion " #condition " failed - "); } } while(0)
#else
#define assert(ignore)((void) 0)
#endif
