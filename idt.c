#include "system.h"

struct idt_p{
    uint32_t base: 32;
    uint32_t limit: 32;
}__attribute__((packed));

struct idt_p pointer;

struct idt_descriptor{
    uint16_t lowoffset: 16;
    uint16_t segselector: 16;
    uint16_t notused: 8;
    uint8_t flags: 8;
    uint16_t highoffset: 16;
}__attribute__((packed));

struct idt_descriptor idt[256];

extern void idt_load();

void idt_set_descriptor(uint32_t baseadress, uint16_t segment, uint8_t flags, uint8_t index)
{
    idt[index].notused = 0; //Not used (as seen on vol 3A of intel documentation)
    idt[index].flags = flags;
    idt[index].segselector = segment;
    idt[index].lowoffset = (baseadress & 0xFFFF);
    idt[index].highoffset = (baseadress >> 16) & 0xFFFF;
}

void idt_init()
{
    pointer.base = (unsigned int) &idt;
    pointer.limit = (sizeof(struct idt_descriptor) * 256) - 1;
    memset(&idt, 0, sizeof(struct idt_descriptor));

    idt_load();
}
