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


global gdt_flush
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10      ; 0x10 offset in GDT to kernel data segment (DS)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:flush2  ; 0x08 offset in GDT to kernel code segment (CS)
flush2:
    ret

global idt_load
extern idtpointer
idt_load:
    lidt [idtpointer]
    ret


extern Isr_handling
global isr_handler
isr_handler:
    ; Save context
    pusha
    push gs
    push fs
    push ds
    push es

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    cld

    ; call the C handling function
    call Isr_handling

    ; Restore context
    pop es
    pop ds
    pop fs
    pop gs
    popa
    iret




; allocate 8kB for .bss section used to stored the stack
[section .bss]

resb 8192
_sys_stack
