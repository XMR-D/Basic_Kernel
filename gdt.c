#include "system.h"

/* Defines a GDT entry.*/

struct gdt_entry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));


/* Special pointer which includes the limit:*/
struct gdt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Our GDT, with 5 entries, and finally our special GDT pointer */
struct gdt_entry gdt[5];
struct gdt_ptr gp;

/* function to reload the GDT our Gdt*/
extern void gdt_flush();


void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* Finally, set up the granularity and access flags */
    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_install()
{
    /* Setup the GDT pointer and limit */
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (unsigned int) &gdt;

    /* NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);

    /* Kernel Code Segment entry */
    gdt_set_gate(1, 0, 0xFFFFF, 0x9A, 0xCF);

    /*Kernel Data Segment entry.*/
    gdt_set_gate(2, 0, 0xFFFFF, 0x92, 0xCF);

    /*Userland Code Segment entry.*/
    gdt_set_gate(3, 0, 0xFFFFF, 0xFA, 0xCF);

    /*Userland Data Segment entry*/
    gdt_set_gate(4, 0, 0xFFFFF, 0XF2, 0xCF);


    /* Flush out the old GDT*/
    gdt_flush();
}
