#include <ctype.h>
#include <strings.h>

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && (tolower(*s1) == tolower(*s2))) {
        s1++;
        s2++;
    }
    char c1 = tolower(*s1);
    char c2 = tolower(*s2);
    if (c1 == c2) {
        return 0;
    }
    if (c1 > c2) {
        return 1;
    }
    if (c1 < c2) {
        return -1;
    }
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        char c1 = tolower(*s1++);
        char c2 = tolower(*s2++);

        if (!c1 && !c2) { // both terminated
            return 0;
        }
        if (c1 > c2) {
            return 1;
        }
        if (c1 < c2) {
            return -1;
        }
    }
    return 0;
}
