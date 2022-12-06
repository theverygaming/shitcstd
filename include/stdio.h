#pragma once
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint32_t fd;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

FILE *fopen(const char *filename, const char *mode); // mode only "r" and "w", binary only
int fclose(FILE *stream);                            // doesn't return EOF, return -1 on failure
size_t fread(void *buffer, size_t size, size_t count, FILE *stream);
size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream);
long ftell(FILE *stream);
int fflush(FILE *stream); // can't flush without a buffer :troll:

// for fseek
#define SEEK_SET 0 /* set file offset to offset */
#define SEEK_CUR 1 /* set file offset to current plus offset */
#define SEEK_END 2 /* set file offset to EOF plus offset */
int fseek(FILE *stream, long offset, int whence);

size_t sscanf(const char *str, const char *fmt, ...);
int fprintf(FILE *stream, const char *fmt, ...);
int printf(const char *fmt, ...);
int snprintf(char *s, size_t n, const char *fmt, ...);
int vsnprintf(char *s, size_t n, const char *fmt, va_list arg);
int vfprintf(FILE *stream, const char *fmt, va_list arg);

int getchar();
int putchar(int c);

int puts(const char *str);

void perror(const char *s);
