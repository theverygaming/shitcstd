.section .text

.global syscall
syscall:
    pusha
    mov 4 * 9(%esp), %eax
    mov 4 * 10(%esp), %ebx
    mov 4 * 11(%esp), %ecx
    mov 4 * 12(%esp), %edx
    mov 4 * 13(%esp), %esi
    mov 4 * 14(%esp), %edi
    mov 4 * 15(%esp), %ebp
    int $0x80
    mov %eax, -1(%esp)
    popa
    mov 4 * -6(%esp), %eax
    ret
