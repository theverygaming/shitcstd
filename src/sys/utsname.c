#include <sys/utsname.h>
#include <linux/syscall.h>

int uname(struct utsname *buf) {
    return sys_uname((struct linux_utsname *)buf);
}
