#include "system.h"

struct cpu {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //pusha
    uint32_t eflags; //eflags register; 
    uint32_t nberr, err_code; //interrupt code
    uint32_t gs, fs, es, ds, ss; //push ds,es,fs,gs,ss
};


// define all ISR here!!

uint32_t err0(struct cpu * context) //divide by 0 exception
{
    puts((unsigned char *) "Exception : Divide by zero.");
    __asm__(
        "cli\n"
        "hlt"
        );
    return 0;
}

uint32_t err1(struct cpu * context) //Debug exception
{
    puts("Error : Divide by 0.");
    return err0;
}

uint32_t err2(struct cpu * context) //NMI Interrupt
{
    puts("Error : Divide by 0.");
    return err0;

}

uint32_t err3(struct cpu * context) //Breakpoint exception
{
    puts("Error : Divide by 0.");
    return err0;

}

uint32_t err4(struct cpu * context) //Overflow exception
{
    puts("Error : Divide by 0.");
    return err0;

}

uint32_t err5(struct cpu * context) //Bound range exceeded exception
{
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err6(struct cpu * context) //Invalid Opcode exception
{
    puts("Error : Divide by 0.");
    return err0;

}

uint32_t err7(struct cpu * context) //Math Coprocessor not available exception
{
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err8(struct cpu * context) //Double fault exception
{
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err9(struct cpu * context) //Coprocessor segment overrun exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err10(struct cpu * context) //Invalid task-state segment exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err11(struct cpu * context) //Segment not present exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err12(struct cpu * context) //Stack-segment fault exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err13(struct cpu * context) //General protection fault exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err14(struct cpu * context) //Page fault
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t reserved(struct cpu * context) //INTEL RESERVED
{
    //TODO : Do nothing reserved isr
    return 0;
}
uint32_t err16(struct cpu * context) //FPU Floating-point error
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err17(struct cpu * context) //Aligment Check exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err18(struct cpu * context) //Machine Check exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}
uint32_t err19(struct cpu * context) //SIMD Floating-point exception
{
    //TODO
    puts("Error : Divide by 0.");
    return err0;

}


typedef uint32_t (*isr_handler)(struct cpu *);

isr_handler jumptable[20] = {err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, reserved, err16, err17, err18, err19};

void Isr_handling(struct cpu * context)
{
    jumptable[context->nberr](context);
}
