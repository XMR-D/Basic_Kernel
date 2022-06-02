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
    uint8_t gatetype : 4;
    uint8_t always0: 1;
    uint8_t DPL: 2;
    uint8_t P: 1;
    uint16_t highoffset: 16;
}__attribute__((packed));

struct idt_descriptor idt[256];

extern void idt_load();

void idt_set_descriptor(uint16_t highoffset, uint16_t lowoffset, uint16_t segment, uint8_t gatetype, uint8_t dpl, uint8_t p, uint8_t index)
{
    idt[index].notused = 0;
    idt[index].always0 = 0;
    idt[index].gatetype = gatetype;
    idt[index].DPL = dpl;
    idt[index].P = p;
    idt[index].segselector = segment;
    idt[index].lowoffset = lowoffset;
    idt[index].highoffset = highoffset;
}

void idt_init()
{
    pointer.base = (unsigned int) &idt;
    pointer.limit = (sizeof(struct idt_descriptor) * 256) - 1;

    idt_set_descriptor(0x0001 , 0x07A3, 0x08, 0b1110, 0, 1, 0);


    memset(&idt, 0, sizeof(struct idt_descriptor));
    idt_load();
}
