#pragma once
#include <abi-calls-default.h>
#include <abi-defs.h>
#include <vix/syscall.h>

#undef ABI_EXIT
#define ABI_EXIT(code) sys_exit(code)

#undef ABI_READ
#define ABI_READ(fd, buf, count) sys_read(fd, buf, count)
#undef ABI_WRITE
#define ABI_WRITE(fd, buf, count) sys_write(fd, buf, count)
