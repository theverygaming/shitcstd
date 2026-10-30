.section .text
.global _start
_start:
#if defined(__FUNNYARCH__)
    mov rfp, #0 // mark end of stack frames

    // int _libc_start(int argc, char **argv, char **envp)
    ldr r0, rsp, #0 // argc
    add r1, rsp, #4 // argv
    add r2, rsp, #8 // envp
    rjal _libc_start

    // exit with return value of _libc_start
    mov r1, r0 // return value from _libc_start
    mov r0, #0 // sys_exit
    int #0x80
.loop:
    rjmp .loop
#else
#error "unsupported architecture"
#endif
