#pragma once
#include <abi-defs.h>

struct utsname {
    char sysname[SHITCSTD_UTSNAME_CHARS+1];
    char nodename[SHITCSTD_UTSNAME_CHARS+1];
    char release[SHITCSTD_UTSNAME_CHARS+1];
    char version[SHITCSTD_UTSNAME_CHARS+1];
    char machine[SHITCSTD_UTSNAME_CHARS+1];
    char domainname[SHITCSTD_UTSNAME_CHARS+1];
};

int uname(struct utsname *buf);
