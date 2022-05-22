[BITS 32]


[section .multiboot]
align 4

dd 0x1badb002
dd 0x0
dd -(0x1badb002 + 0x0)


[section .text]
[global start]

start:
    mov esp, _sys_stack
    jmp stublet


; endless loop where we call main and other functions.
stublet:
    extern main
    call main
    jmp $


; //TODO GDT here

; //TODO ISR here

; allocate 8kB for .bss section used to stored the stack
[section .bss]

resb 8192
_sys_stack:

