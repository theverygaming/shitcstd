#pragma once

#include <stdint.h>

#define NULL ((void *)0)

#if defined(__SIZE_TYPE__) && defined(__SIZE_MAX__)
typedef __SIZE_TYPE__ size_t;
#undef SIZE_MAX
#define SIZE_MAX __SIZE_MAX__
#else
#error "compiler does not provide __SIZE_TYPE__ or __SIZE_MAX__"
#endif

typedef intptr_t ssize_t;
