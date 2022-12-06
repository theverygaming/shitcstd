#pragma once
#define va_list __builtin_va_list
#define va_start(v, l) __builtin_va_start((v), (l))
#define va_arg __builtin_va_arg
#define va_end __builtin_va_end
