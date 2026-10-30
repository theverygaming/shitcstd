.section .text
.global syscall
syscall:
#if defined(__FUNNYARCH__)
    // r0-r6 contain syscall number and 6 arguments
    int #0x80
    mov rip, lr
#else
#error "unsupported architecture"
#endif
