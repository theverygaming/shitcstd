#include <sys/utsname.h>
#include <abi-calls.h>

int uname(struct utsname *buf) {
    return ABI_UNAME(buf);
}
