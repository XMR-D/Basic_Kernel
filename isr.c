#include "system.h"

struct cpu {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //pusha
    uint32_t eflags; //eflags register; 
    uint32_t nberr, err_code; //interrupt code
    uint32_t gs, fs, es, ds, ss; //push ds,es,fs,gs,ss
};


// define all ISR here!!

void err0(volatile struct cpu * context) //divide by 0 exception
{
    puts((unsigned char *) "Exception : Divide by zero.");
    asm("cli");
    asm("hlt");
}

void err1(volatile struct cpu * context) //Debug exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}

void err2(volatile struct cpu * context) //NMI Interrupt
{
    puts((unsigned char *) "Error : Divide by 0.");
}

void err3(volatile struct cpu * context) //Breakpoint exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}

void err4(volatile struct cpu * context) //Overflow exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}

void err5(volatile struct cpu * context) //Bound range exceeded exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}
void err6(volatile struct cpu * context) //Invalid Opcode exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}

void err7(volatile struct cpu * context) //Math Coprocessor not available exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}
void err8(volatile struct cpu * context) //Double fault exception
{
    puts((unsigned char *) "Error : Divide by 0.");
}
void err9(volatile struct cpu * context) //Coprocessor segment overrun exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err10(volatile struct cpu * context) //Invalid task-state segment exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err11(volatile struct cpu * context) //Segment not present exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err12(volatile struct cpu * context) //Stack-segment fault exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err13(volatile struct cpu * context) //General protection fault exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err14(volatile struct cpu * context) //Page fault
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void reserved(volatile struct cpu * context) //INTEL RESERVED
{
    //TODO : Do nothing reserved isr
}
void err16(volatile struct cpu * context) //FPU Floating-point error
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err17(volatile struct cpu * context) //Aligment Check exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err18(volatile struct cpu * context) //Machine Check exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0.");
}
void err19(volatile struct cpu * context) //SIMD Floating-point exception
{
    //TODO
    puts((unsigned char *) "Error : Divide by 0."); 
}

typedef void (*Handler)(volatile struct cpu * context);

Handler jumptable[20] = {err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, reserved, err16, err17, err18, err19};

void Isr_handling(volatile struct cpu context)
{
    jumptable[context.nberr](&context);

}
