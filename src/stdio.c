#include <abi-calls.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libc-init.h>
#include "helpers.h"

FILE *stdin;
FILE *stdout;
FILE *stderr;

void _libc_init_stdio() {
    static FILE stdin_d = {STDIN_FILENO};
    static FILE stdout_d = {STDOUT_FILENO};
    static FILE stderr_d = {STDERR_FILENO};
    
    stdin = &stdin_d;
    stdout = &stdout_d;
    stderr = &stderr_d;
}

FILE *fopen(const char *filename, const char *mode) {
    bool read = false;
    bool write = false;
    while (*mode) {
        switch (*mode++) {
        case 'r':
            read = true;
            break;
        case 'w':
            write = true;
            break;
        default:
            break;
        }
    }
    int flags = 0;
    if (read && !write) {
        flags = ABI_O_RDONLY;
    } else if (!read && write) {
        flags = ABI_O_WRONLY;
    } else if (read && write) {
        flags = ABI_O_RDWR;
    }

    int fd = open(filename, flags, 0);
    if (fd < 0) {
        return 0;
    }
    FILE *stream = (FILE *)malloc(sizeof(FILE));
    FILE file = {
        .fd = fd,
    };
    *stream = file;
    return stream;
}

int fclose(FILE *stream) {
    if (close(stream->fd) < 0) {
        return -1;
    }
    return 0;
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream) {
    if ((count * size) == 0) {
        return 0;
    }
    ssize_t nread = read(stream->fd, buffer, size * count);
    if (nread < 0) {
        return 0;
    }
    return ((size_t)nread) / size;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream) {
    if ((count * size) == 0) {
        return 0;
    }
    ssize_t written = write(stream->fd, buffer, size * count);
    if (written < 0) {
        return 0;
    }
    return ((size_t)written) / size;
}

long ftell(FILE *stream) {
    off_t pos = lseek(stream->fd, 0, SEEK_CUR);
    if (pos < 0) {
        return -1;
    }
    return pos;
}

int fseek(FILE *stream, long offset, int whence) {
    if (lseek(stream->fd, offset, whence) < 0) {
        return -1;
    }
    return 0;
}

int fflush(FILE *stream) {
    return 0;
}

size_t sscanf(const char *str, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    size_t instrcnt = 0;
    size_t items_filled = 0;
    while (*fmt) {
        if (str[instrcnt] == 0) {
            goto ret;
        }
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
            case 's': {
                char fmtcut[100];
                size_t cspn = strcspn(fmt + 1, "%");
                if (cspn >= 100) {
                    goto ret;
                }
                memcpy(fmtcut, fmt + 1, cspn);
                fmtcut[cspn] = '\0';

                size_t cpcnt = (size_t)strstr(&str[instrcnt], fmtcut);
                if (!cpcnt) {
                    goto ret;
                }
                cpcnt -= (size_t)&str[instrcnt];
                if (!cpcnt) {
                    cpcnt = strlen(&str[instrcnt]);
                }
                char *arg = va_arg(args, char *);
                memcpy((void *)arg, (void *)&str[instrcnt], cpcnt);
                instrcnt += cpcnt - 1;

                items_filled++;
                break;
            }
            case 'l': {
                if (*(fmt + 1) == 'u') {
                    fmt++;
                    unsigned long int *arg = va_arg(args, unsigned long int *);
                    char *str_after;
                    *arg = strtoul(&str[instrcnt], &str_after, 10);
                    instrcnt += (str_after - &str[instrcnt]) - 1;
                    items_filled++;
                    break;
                }
            }
            default: {
                fprintf(stderr, "sscanf: unsupported %%%c\n", *fmt);
                break;
            }
            }
        }
        instrcnt++;
        fmt++;
    }
ret:
    va_end(args);
    return items_filled;
}

#define PF_FMT_FLAG_LEFT_JUSTIFIED (1 << 0)
#define PF_FMT_FLAG_LEADING_ZEROS (1 << 1)
#define PF_FMT_FLAG_SHOW_POSITIVE_PLUS (1 << 2)
#define PF_FMT_FLAG_SHOW_POSITIVE_SPACE (1 << 3)
#define PF_FMT_FLAG_ALTERNATIVE (1 << 4)
#define PF_FMT_PRECISION_NOT_SPECIFIED (-1)
static const char *printf_parse_format_fields(va_list args, const char *fmt, unsigned int *flags, unsigned int *min_width, int *precision) {
    *flags = 0;
    *min_width = 0;
    *precision = PF_FMT_PRECISION_NOT_SPECIFIED;

    if (*fmt == '\0') {
        return fmt;
    }

    // first check if there's any flags
    while (*fmt == '-' || *fmt == '0' || *fmt == '+' || *fmt == ' ' || *fmt == '#') {
        switch(*fmt) {
            case '-': {
                *flags |= PF_FMT_FLAG_LEFT_JUSTIFIED;
                break;
            }
            case '0': {
                *flags |= PF_FMT_FLAG_LEADING_ZEROS;
                break;
            }
            case '+': {
                *flags |= PF_FMT_FLAG_SHOW_POSITIVE_PLUS;
                break;
            }
            case ' ': {
                *flags |= PF_FMT_FLAG_SHOW_POSITIVE_SPACE;
                break;
            }
            case '#': {
                *flags |= PF_FMT_FLAG_ALTERNATIVE;
                break;
            }
        }
        fmt++;
    }
    if (*fmt == '\0') {
        return fmt;
    }

    // minimum field width
    if (*fmt == '*') {
        int width = va_arg(args, int);
        if (width < 0) {
            *flags |= PF_FMT_FLAG_LEFT_JUSTIFIED;
            width = -width;
        }
        *min_width = width;
        fmt++;
    } else {
        const char *start = fmt;
        while (*fmt >= '0' && *fmt <= '9') {
            fmt++;
        }
        size_t n = fmt - start;
        if (n != 0) {
            *min_width = shitcstd_atoi_sized(start, n);
        }
    }
    if (*fmt == '\0') {
        return fmt;
    }

    // precision
    if (*fmt == '.') {
        fmt++;
        if (*fmt == '\0') {
            return fmt;
        }
        if (*fmt == '*') {
            int a_precision = va_arg(args, int);
            if (a_precision >= 0) {
                *precision = a_precision;
            }
            fmt++;
        } else {
            const char *start = fmt;
            while (*fmt >= '0' && *fmt <= '9') {
                fmt++;
            }
            size_t n = fmt - start;
            if (n != 0) {
                *precision = shitcstd_atoi_sized(start, n);
            } else {
                // No number after . -> zero precision
                *precision = 0;
                fmt++;
            }
        }
    }
    if (*fmt == '\0') {
        return fmt;
    }

    return fmt;
}

static int printf_base(va_list args, const char *fmt, FILE *stream, char *buf, bool buf_write, size_t buf_len) {
    size_t chars_written = 0;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            unsigned int fmt_flags;
            unsigned int min_width;
            int precision;
            fmt = printf_parse_format_fields(args, fmt, &fmt_flags, &min_width, &precision);

            switch (*fmt) {
            case '%': {
                fmt += 1;
                if (buf_write) {
                    size_t can_write = (buf_len - 1) - chars_written;
                    if (chars_written > (buf_len - 1)) {
                        can_write = 0;
                    }
                    if (can_write >= 1) {
                        memcpy(&buf[chars_written], "%", 1);
                    } else {
                        memcpy(&buf[chars_written], "%", can_write);
                    }
                } else {
                    write(stream->fd, "%", 1);
                }
                chars_written += 1;
                break;
            }
            case 's': {
                fmt += 1;
                const char *arg = va_arg(args, const char *);
                if (buf_write) {
                    size_t can_write = (buf_len - 1) - chars_written;
                    if (chars_written > (buf_len - 1)) {
                        can_write = 0;
                    }
                    if (can_write >= strlen(arg)) {
                        memcpy(&buf[chars_written], arg, strlen(arg));
                    } else {
                        memcpy(&buf[chars_written], arg, can_write);
                    }
                } else {
                    write(stream->fd, arg, strlen(arg));
                }
                chars_written += strlen(arg);
                break;
            }
            case 'u': {
                fmt += 1;
                unsigned int arg = va_arg(args, unsigned int);
                char n_buf[11];
                char *ret = itoa(arg, n_buf, 10);
                if (buf_write) {
                    size_t can_write = (buf_len - 1) - chars_written;
                    if (chars_written > (buf_len - 1)) {
                        can_write = 0;
                    }
                    if (can_write >= strlen(ret)) {
                        memcpy(&buf[chars_written], ret, strlen(ret));
                    } else {
                        memcpy(&buf[chars_written], ret, can_write);
                    }
                } else {
                    write(stream->fd, ret, strlen(ret));
                }
                chars_written += strlen(ret);
                break;
            }
            case 'i':
            case 'd': {
                fmt += 1;
                int arg = va_arg(args, int);
                char n_buf[12];
                char *ret = itoa_signed(arg, n_buf, 10);
                if (precision != PF_FMT_PRECISION_NOT_SPECIFIED) {
                    // FIXME: HACK: this is very cursed and will break horribly with negative numbers (example: 000-123) :)
                    size_t l = strlen(ret);
                    if (l < precision) {
                        size_t pad = precision - l;
                        while (pad != 0) {
                            if (buf_write) {
                                size_t can_write = (buf_len - 1) - chars_written;
                                if (chars_written > (buf_len - 1)) {
                                    can_write = 0;
                                }
                                if (can_write >= 1) {
                                    buf[chars_written] = '0';
                                }
                            } else {
                                char w = '0';
                                write(stream->fd, &w, 1);
                            }
                            chars_written++;
                            pad--;
                        }
                    }
                }
                if (buf_write) {
                    size_t can_write = (buf_len - 1) - chars_written;
                    if (chars_written > (buf_len - 1)) {
                        can_write = 0;
                    }
                    if (can_write >= strlen(ret)) {
                        memcpy(&buf[chars_written], ret, strlen(ret));
                    } else {
                        memcpy(&buf[chars_written], ret, can_write);
                    }
                } else {
                    write(stream->fd, ret, strlen(ret));
                }
                chars_written += strlen(ret);
                break;
            }
            case 'c': {
                fmt += 1;
                char arg = va_arg(args, int);
                if (buf_write) {
                    size_t can_write = (buf_len - 1) - chars_written;
                    if (chars_written > (buf_len - 1)) {
                        can_write = 0;
                    }
                    if (can_write >= 1) {
                        memcpy(&buf[chars_written], &arg, 1);
                    } else {
                        memcpy(&buf[chars_written], &arg, can_write);
                    }
                } else {
                    write(stream->fd, &arg, 1);
                }
                chars_written++;
                break;
            }
            default:
            fprintf(stderr, "printf: unsupported %%%c\n", *fmt);
            break;
            }
        }
        size_t count = strcspn(fmt, "%");
        if (buf_write) {
            size_t can_write = (buf_len - 1) - chars_written;
            if (chars_written > (buf_len - 1)) {
                can_write = 0;
            }
            if (can_write >= count) {
                memcpy(&buf[chars_written], fmt, count);
            } else {
                memcpy(&buf[chars_written], fmt, can_write);
            }
        } else {
            write(stream->fd, fmt, count);
        }
        chars_written += count;
        fmt += count;
    }
    if (buf_write) {
        if (chars_written < (buf_len - 1)) {
            buf[chars_written] = '\0';
        } else {
            buf[buf_len - 1] = '\0';
        }
    }

    return chars_written;
}

int fprintf(FILE *stream, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = printf_base(args, fmt, stream, NULL, false, 0);
    va_end(args);
    return ret;
}

int printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = printf_base(args, fmt, stdout, NULL, false, 0);
    va_end(args);
    return ret;
}

int snprintf(char *s, size_t n, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int ret = printf_base(args, fmt, 0, s, true, n);
    va_end(args);
    return ret;
}

int vsnprintf(char *s, size_t n, const char *fmt, va_list arg) {
    return printf_base(arg, fmt, 0, s, true, n);
}
int vfprintf(FILE *stream, const char *fmt, va_list arg) {
    return printf_base(arg, fmt, stream, 0, false, 0);
}

int getchar() {
    char buf;
    read(STDIN_FILENO, &buf, 1);
    return (int)buf;
}

int putchar(int c) {
    write(STDOUT_FILENO, &c, 1);
    return c;
}

int puts(const char *str) {
    size_t len = strlen(str);
    write(STDOUT_FILENO, str, len);
    return 0;
}

void perror(const char *s) {
    if (s != NULL) {
        printf("%s: \n", s);
    }
}

int rename(const char *old, const char *new) {
    return ABI_RENAME(ABI_AT_FDCWD, old, ABI_AT_FDCWD, new, 0);
}

int remove(const char *pathname) {
    int status = ABI_UNLINKAT(ABI_AT_FDCWD, pathname, 0);
    if (status == ABI_EISDIR) {
        status = ABI_UNLINKAT(ABI_AT_FDCWD, pathname, ABI_UNLINKAT_REMOVEDIR);
    }
    return status;
}
