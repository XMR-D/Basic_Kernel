#include "system.h"

struct idt_p{
    uint32_t base: 32;
    uint32_t limit: 32;
}__attribute__((packed));

struct idt_p pointer;

extern void isr_handler();

struct idt_descriptor{
    uint16_t lowoffset: 16;
    uint16_t segselector: 16;
    uint8_t notused : 8;
    uint8_t flags: 8;
    uint16_t highoffset: 16;
}__attribute__((packed));

struct idt_descriptor idt[256];

extern void idt_load();

void idt_set_descriptor(uint32_t baseadress, uint16_t segment, uint8_t flags, uint8_t index)
{
    idt[index].notused = 0;
    idt[index].flags = flags;
    idt[index].segselector = segment;
    idt[index].lowoffset = (baseadress & 0xFFFF);
    idt[index].highoffset = (baseadress >> 16) & 0xFFFF;
}

void idt_init()
{
    pointer.base = (unsigned int) &idt;
    pointer.limit = (sizeof(struct idt_descriptor) * 256) - 1;
 
    //idt_set_descriptor calls
    idt_set_descriptor((uint32_t) isr_handler, 0x08, 0x8E, 0);
    /*
    idt_set_descriptor(0x10822, 0x10, 0x8E, 1);

    //intel reserved
    idt_set_descriptor(0x10822, 0x10, 0xE, 2);

    idt_set_descriptor(0x10822, 0x10, 0x8E00, 3);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 4);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 5);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 6);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 7);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 8);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 9);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 10);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 11);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 12);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 13);
    idt_set_descriptor(0x10822, 0x10, 0x8E00, 14);

    //intel reserved
    idt_set_descriptor(0x10822, 0x10, 0xE00, 15);

    idt_set_descriptor(0x10822, 0x10, 0x8E00, 16);

    */
    memset(&idt, 0, sizeof(struct idt_descriptor));

    idt_load();
}
