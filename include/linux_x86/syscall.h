#pragma once
#include <stddef.h>
#include <sys/types.h>
#include <time.h>

extern uint32_t syscall(uint32_t syscall_num, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, uint32_t a6);

void sys_exit(int error_code);
pid_t sys_fork();
uint32_t sys_read(uint32_t fd, void *buf, size_t count);
int sys_write(uint32_t fd, const void *buf, size_t count);

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2
#define O_CREAT 100
#define O_EXCL 200
#define O_NOCTTY 400
#define O_TRUNC 1000
#define O_APPEND 2000
#define O_NONBLOCK 4000
#define O_NDELAY O_NONBLOCK
#define O_SYNC 10000
#define O_FSYNC O_SYNC
#define O_ASYNC 20000
typedef unsigned short umode_t;
int sys_open(const char *filename, int flags, umode_t mode);
int sys_close(unsigned int fd);
void sys_waitpid(pid_t pid, int *stat_addr, int options);
void sys_execve(const char *filename, char *const *argv, const char *const *envp);
int sys_chdir(const char *filename);
void sys_time(time_t *tloc);
off_t sys_lseek(unsigned int fd, off_t offset, unsigned int whence);
int sys_brk(void *addr);

// https://man7.org/linux/man-pages/man2/sysinfo.2.html
struct sysinfo {
    long uptime;                                  /* Seconds since boot */
    unsigned long loads[3];                       /* 1, 5, and 15 minute load averages */
    unsigned long totalram;                       /* Total usable main memory size */
    unsigned long freeram;                        /* Available memory size */
    unsigned long sharedram;                      /* Amount of shared memory */
    unsigned long bufferram;                      /* Memory used by buffers */
    unsigned long totalswap;                      /* Total swap space size */
    unsigned long freeswap;                       /* Swap space still available */
    unsigned short procs;                         /* Number of current processes */
    unsigned long totalhigh;                      /* Total high memory size */
    unsigned long freehigh;                       /* Available high memory size */
    unsigned int mem_unit;                        /* Memory unit size in bytes */
    char _f[20 - 2 * sizeof(long) - sizeof(int)]; /* Padding to 64 bytes */
};

int sys_sysinfo(struct sysinfo *info);

struct utsname {
    char sysname[65];
    char nodename[65];
    char release[65];
    char version[65];
    char machine[65];
    char domainname[65];
};

int sys_uname(struct utsname *buf);
char *sys_getcwd(char *buf, size_t size);
