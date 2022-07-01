#include "system.h"

struct cpu{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t eflags;
    uint32_t nberr, err_code;
    uint32_t gs, fs, es, ds, ss;
};

extern void irq_handler();

void irq0()
{
    printf((unsigned char *) "IRQ %u triggered\n", 0);
}

void irq1()
{
    keyboard_handling();
}

void irq2()
{
    printf((unsigned char *) "IRQ %u triggered\n", 2);
}

void irq3()
{
    printf((unsigned char *) "IRQ %u triggered\n", 3);
}

void irq4()
{
    printf((unsigned char *) "IRQ %u triggered\n", 4);
}

void irq5()
{
    printf((unsigned char *) "IRQ %u triggered\n", 5);
}

void irq6()
{
    printf((unsigned char *) "IRQ %u triggered\n", 6);
}

void irq7()
{
    printf((unsigned char *) "IRQ %u triggered\n", 7);
}

void irq8()
{
    printf((unsigned char *) "IRQ %u triggered\n", 8);
}

void irq9()
{
    printf((unsigned char *) "IRQ %u triggered\n", 9);
}

void irq10()
{
    printf((unsigned char *) "IRQ %u triggered\n", 10);
}

void irq11()
{
    printf((unsigned char *) "IRQ %u triggered\n", 11);
}

void irq12()
{
    printf((unsigned char *) "IRQ %u triggered\n", 12);
}

void irq13()
{
    printf((unsigned char *) "IRQ %u triggered\n", 13);
}

void irq14()
{
    printf((unsigned char *) "IRQ %u triggered\n", 14);
}

void irq15()
{
    printf((unsigned char *) "IRQ %u triggered\n", 15);
}

typedef void (*Handler)(void);

Handler jumptableirq[16] = {irq0, irq1, irq2, irq3, irq4, irq5, irq6, irq7, irq8, irq9, irq10, irq11, irq12, irq13, irq14, irq15};

void Basic_irq_handling(volatile struct cpu context)
{
    jumptableirq[context.nberr+32]();
}



void irq_remap()
{
    //save currents masks
    uint8_t mask1 = inb(0x21);
    uint8_t mask2 = inb(0xA1);

    //ICW1 -- initialisation begin
    outb(0x20, 0x11);

    outb(0x80, 0); //wait

    outb(0xA0, 0x11);

    outb(0x80, 0); //wait

    //ICW2 -- remap interrupt numbers
    outb(0x21, 0x20);

    outb(0x80, 0); //wait

    outb(0xA1 , 0x28);

    outb(0x80, 0); //wait

    //ICW3 -- make the two pic communicate
    outb(0x21, 0x04);

    outb(0x80, 0); //wait

    outb(0xA1, 0x02);

    outb(0x80, 0); //wait

    //ICW4
    outb(0x21, 0x01);

    outb(0x80, 0); //wait

    outb(0xA1, 0x01);

    outb(0x80, 0); //wait

    //Finished -- data register reinitialisation with saved masks
    outb(0x21, mask1);
    outb(0xA1, mask2);

   //asm volatile("iret");
}
