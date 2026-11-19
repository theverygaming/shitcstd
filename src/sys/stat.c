#include <sys/stat.h>
#include <abi-calls.h>

int mkdir(const char *path, mode_t mode) {
    return ABI_MKDIRAT(ABI_AT_FDCWD, path, mode);
}

int mkdirat(int dirfd, const char *path, mode_t mode) {
    return ABI_MKDIRAT(dirfd, path, mode);
}
