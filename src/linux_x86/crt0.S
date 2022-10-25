.section .text
.global  _start
.extern main

_start:
    xor %ebp, %ebp // mark end of stack frames
    
    mov (%esp), %edi // argc
    lea 4(%esp), %esi // argv
    lea 8(%esp, %edi, 4), %edx // envp
    push %edx // envp
    push %esi // argv
    push %edi // argc

    xor %eax, %eax

    call main // call C start function main(int argc, char* argv[], char* envp_str)
    
    // exit with return value of main
    mov %eax, %ebx // main returns in eax
    mov $1, %eax // sys_exit
    int $0x80
.loop:
    hlt // if we are here something went wrong badly
    jmp .loop
