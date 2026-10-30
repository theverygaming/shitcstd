.section .text
.global  _start
.extern _libc_start

_start:
#if defined(__i386__)
    xor %ebp, %ebp // mark end of stack frames

    mov (%esp), %edi // argc
    lea 4(%esp), %esi // argv
    lea 8(%esp, %edi, 4), %edx // envp
    push %edx // envp
    push %esi // argv
    push %edi // argc

    xor %eax, %eax

    call _libc_start // call C start function _libc_start(int argc, char* argv[], char* envp_str)

    // exit with return value of _libc_start
    mov %eax, %ebx // _libc_start returns in eax
    mov $1, %eax // sys_exit
    int $0x80
    ud2
.loop:
    jmp .loop
#elif defined(__x86_64__)
    call _libc_start // call C start function _libc_start(int argc, char* argv[], char* envp_str)

    // exit with return value of _libc_start
    mov %rax, %rdi // _libc_start returns in rax
    mov $1, %rax // sys_exit
    syscall
    ud2
.loop:
    jmp .loop
#else
#error "unsupported architecture"
#endif
