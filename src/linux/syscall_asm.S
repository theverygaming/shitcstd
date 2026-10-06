.section .text

.global syscall
syscall:
#if defined(__i386__)
    pusha
    mov 4 * 9(%esp), %eax
    mov 4 * 10(%esp), %ebx
    mov 4 * 11(%esp), %ecx
    mov 4 * 12(%esp), %edx
    mov 4 * 13(%esp), %esi
    mov 4 * 14(%esp), %edi
    mov 4 * 15(%esp), %ebp
    int $0x80
    mov %eax, 4 * 7(%esp)
    popa
    ret
#elif defined(__x86_64__)
    mov %rdi, %rax
    mov %rsi, %rdi
    mov %rdx, %rsi
    mov %rcx, %rdx
    mov %r8, %r10
    mov %r9, %r8
    mov 8(%rsp), %r9
    syscall
    // return in %rax, fits ABI
    ret
#else
#error "unsupported architecture"
#endif
