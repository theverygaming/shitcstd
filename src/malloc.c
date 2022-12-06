#include <linux_x86/syscall.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct allocinfo {
    size_t allocsize;
};

void *malloc(size_t size) {
    void *current = sbrk(0);
    if (sbrk(size + sizeof(struct allocinfo)) == (void *)-1) {
        printf("out of memory\n");
        exit(1);
        return 0;
    }

    struct allocinfo *info = (struct allocinfo *)current;
    info->allocsize = size;
    return ((char *)current) + sizeof(struct allocinfo);
}

void *realloc(void *ptr, size_t size) {
    if (ptr == 0) {
        if (size == 0) {
            return 0;
        }
        return malloc(size);
    }
    struct allocinfo *info = (struct allocinfo *)(((char *)ptr) - sizeof(struct allocinfo));
    void *ret = malloc(size);
    memcpy(ret, ptr, info->allocsize);
    free(ptr);
    return ret;
}

void free(void *ptr) {} // :troll:

void *calloc(size_t num, size_t size) {
    void *ptr = malloc(num * size);
    memset(ptr, 0, num * size);
    return ptr;
}
