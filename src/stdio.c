#include <linux_x86/syscall.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE stdin_d = {STDIN_FILENO};
FILE stdout_d = {STDOUT_FILENO};
FILE stderr_d = {STDERR_FILENO};

FILE *stdin = &stdin_d;
FILE *stdout = &stdout_d;
FILE *stderr = &stderr_d;

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
        flags = O_RDONLY;
    } else if (!read && write) {
        flags = O_WRONLY;
    } else if (read && write) {
        flags = O_RDWR;
    }

    int fd = sys_open(filename, flags, 0);
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
    if (sys_close(stream->fd) < 0) {
        return -1;
    }
    return 0;
}

size_t fread(void *buffer, size_t size, size_t count, FILE *stream) {
    if ((count * size) == 0) {
        return 0;
    }
    ssize_t read = sys_read(stream->fd, buffer, size * count);
    if (read < 0) {
        return 0;
    }
    return ((size_t)read) / size;
}

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream) {
    if ((count * size) == 0) {
        return 0;
    }
    ssize_t written = sys_write(stream->fd, buffer, size * count);
    if (written < 0) {
        return 0;
    }
    return ((size_t)written) / size;
}

long ftell(FILE *stream) {
    off_t pos = sys_lseek(stream->fd, 0, SEEK_CUR);
    if (pos < 0) {
        return -1;
    }
    return pos;
}

int fseek(FILE *stream, long offset, int whence) {
    if (sys_lseek(stream->fd, offset, whence) < 0) {
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
            }
        }
        instrcnt++;
        fmt++;
    }
ret:
    va_end(args);
    return items_filled;
}

static int printf_base(va_list args, const char *fmt, FILE *stream, char *buf, bool buf_write, size_t buf_len) {
    size_t chars_written = 0;
    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
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
                    sys_write(stream->fd, "%", 1);
                }
                chars_written += 1;
                break;
            }
            case 's': {
                fmt += 1;
                char *arg = va_arg(args, char *);
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
                    sys_write(stream->fd, arg, strlen(arg));
                }
                chars_written += strlen(arg);
                break;
            }
            case 'u': {
                fmt += 1;
                size_t arg = va_arg(args, size_t);
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
                    sys_write(stream->fd, ret, strlen(ret));
                }
                chars_written += strlen(ret);
                break;
            }
            case 'd': {
                fmt += 1;
                size_t arg = va_arg(args, size_t);
                char n_buf[12];
                char *ret = itoa_signed(arg, n_buf, 10);
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
                    sys_write(stream->fd, ret, strlen(ret));
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
                    sys_write(stream->fd, &arg, 1);
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
            sys_write(stream->fd, fmt, count);
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
    sys_read(STDIN_FILENO, &buf, 1);
    return (int)buf;
}

int putchar(int c) {
    sys_write(STDOUT_FILENO, &c, 1);
    return c;
}

int puts(const char *str) {
    size_t len = strlen(str);
    sys_write(STDOUT_FILENO, str, len);
    return 0;
}

void perror(const char *s) {
    if (s != NULL) {
        printf("%s: \n", s);
    }
}
