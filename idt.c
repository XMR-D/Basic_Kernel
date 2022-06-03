#include "system.h"

struct idtr_p{
    uint32_t offset: 32;
    uint16_t size: 16;
}__attribute__((packed));

struct idtr_p pointer;

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

static struct idt_descriptor idt[256];

extern void idt_load();

void idt_set_descriptor(uint32_t offset, uint16_t segment, uint8_t gatetype, uint8_t dpl, uint8_t p, uint8_t index)
{
    idt[index].notused = 0;
    idt[index].always0 = 0;
    idt[index].gatetype = gatetype;
    idt[index].DPL = dpl;
    idt[index].P = p;
    idt[index].segselector = segment;
    idt[index].lowoffset = (offset & 0xFFFF);
    idt[index].highoffset = (offset >> 16) & 0xFFFF;
}

void idt_init()
{
    pointer.offset = (unsigned int) &idt;
    pointer.size = (sizeof(struct idt_descriptor) * 256) - 1;
    memset(&idt, 0, sizeof(struct idt_descriptor));

    idt_set_descriptor((uint32_t) err0, 0x08, 0b1110, 0, 1, 0);

    idt_load();

}
