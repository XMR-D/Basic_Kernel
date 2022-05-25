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

global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10      ; 0x10 offset in GDT to data segment (DS)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2  ; 0x08 offset in GDT to code segment (CS)
flush2:
    ret              ;back to C

; //TODO ISR here

; allocate 8kB for .bss section used to stored the stack
[section .bss]

resb 8192
_sys_stack
