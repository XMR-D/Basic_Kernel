#include "system.h"

struct cpu {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //pusha
    uint32_t eflags; //eflags register; 
    uint32_t nberr, err_code; //interrupt code
    uint32_t gs, fs, es, ds, ss; //push ds,es,fs,gs,ss
};


// define all ISR here!!

void err0() //divide by 0 exceptioni (FAULT)
{
    puts((unsigned char *) "Exception : Division by zero.");
    asm volatile("cli");
    asm volatile("hlt");
}

void err1() //Debug exception (FAULT/TRAP)
{
    puts((unsigned char *) "Exception : Debug exception.");
    asm volatile("cli");
    asm volatile("hlt");

}

void err2() //NMI Interrupt (INTERRUPT)
{
    puts((unsigned char *) "Exception : Non maskable interrupt.");
    asm volatile("cli");
    asm volatile("hlt");
}

void err3() //Breakpoint exception (TRAP)
{
    puts((unsigned char *) "Breakpoint.");
    asm volatile("cli");
    asm volatile("hlt");
}

void err4() //Overflow exception (TRAP)
{
    puts((unsigned char *) "Exception : Overflow exception.");
    asm volatile("cli");
    asm volatile("hlt");
}

void err5() //Bound range exceeded exception (FAULT)
{
    puts((unsigned char *) "Exception : Bound range exceeded.");
    asm volatile("cli");
    asm volatile("hlt");
}

void err6() //Invalid Opcode exception (FAULT)
{
    puts((unsigned char *) "Exception : Invalid Opcode.");
    asm volatile("cli");
    asm volatile("hlt");

}

void err7() //Math Coprocessor not available exception (FAULT)
{
    puts((unsigned char *) "Exception : Math Coprocessor not available.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err8() //Double fault exception (ABORT)
{
    puts((unsigned char *) "Exception : Double Fault.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err9() //Coprocessor segment overrun exception (FAULT)
{
    puts((unsigned char *) "Exception : Coprocessor segment overrun.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err10() //Invalid task-state segment exception (FAULT)
{
    puts((unsigned char *) "Exception : Invalid TSS (task-state segment).");
    asm volatile("cli");
    asm volatile("hlt");
}
void err11() //Segment not present exception (FAULT)
{
    puts((unsigned char *) "Exception : Missing segment.");
    asm volatile("cli");
    asm volatile("hlt");
}
void err12() //Stack-segment fault exception (FAULT)
{
    puts((unsigned char *) "Exception : Stack-segment fault exception.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err13() //General protection fault exception (FAULT)
{
    puts((unsigned char *) "Exception : General protection fault.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err14() //Page fault (FAULT)
{
    puts((unsigned char *) "Exception : Page fault.");
    asm volatile("cli");
    asm volatile("hlt");

}
void reserved() //INTEL RESERVED
{
    puts((unsigned char *) "RESERVED.");
    asm volatile("cli");
    asm volatile("hlt");
}
void err16() //FPU Floating-point error (FAULT)
{
    puts((unsigned char *) "Exception: Floating-point Error.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err17() //Aligment Check exception (FAULT)
{
    puts((unsigned char *) "Exception : ALigment Check exception.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err18() //Machine Check exception (ABORT)
{
    puts((unsigned char *) "Exception : Machine Check exception.");
    asm volatile("cli");
    asm volatile("hlt");

}
void err19() //SIMD Floating-point exception (FAULT)
{
    puts((unsigned char *) "Exception : SIMD Floating-point exception.");
    asm volatile("cli");
    asm volatile("hlt");

}

typedef void (*Handler)(void);

Handler jumptable[20] = {err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, reserved, err16, err17, err18, err19};

void Basic_isr_handling(volatile struct cpu context)
{
    jumptable[context.nberr]();
}
