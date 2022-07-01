#include "system.h"

struct idtr{
    uint16_t size : 16;
    uint32_t idt_adress : 32;
}__attribute__((packed));

struct idt_gate_descriptor{
    uint16_t lowoffset : 16;
    uint16_t codeselect : 16;
    uint8_t reserved : 8;
    uint8_t gatetype : 4;
    uint8_t always0 : 1;
    uint8_t dpl: 2;
    uint8_t p : 1;
    uint16_t highoffset : 16;
}__attribute__((packed));

struct idtr idtpointer;
extern void idt_load();
extern void isr_handler();
extern void irq_handler();
static struct idt_gate_descriptor idt[256];

void idt_set_gate(uint8_t num, uint32_t o, uint16_t c_s, uint8_t g_t, uint8_t dpl, uint8_t p)
{
    idt[num].lowoffset = (o & 0xFFFF);
    idt[num].codeselect = c_s;
    idt[num].reserved = 0;
    idt[num].gatetype = g_t;
    idt[num].always0 = 0;
    idt[num].dpl = dpl;
    idt[num].p = p;
    idt[num].highoffset = (o >> 16) & 0xFFFF;

}

void idt_format()
{
    for(int i = 0; i <= 255; i++)
    {
        idt_set_gate(i, 0, 0, 0, 0, 0);
    }
}

void idt_init()
{
    idtpointer.size = (sizeof(struct idt_gate_descriptor)*256)-1;
    idtpointer.idt_adress = (unsigned int) &idt;

    idt_format();

    // Basics ones
    idt_set_gate(0, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(1, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);

    idt_set_gate(2, (unsigned int) &(isr_handler)+1, 0x8, 0b1110, 0, 1);

    idt_set_gate(3, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(4, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(5, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(6, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(7, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);

    idt_set_gate(8, (unsigned int) &(isr_handler)+1, 0x8, 0b1110, 0, 1);

    idt_set_gate(9, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(10, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(11, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(12, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(13, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(14, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(15, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(16, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);
    idt_set_gate(17, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);

    idt_set_gate(18, (unsigned int) &(isr_handler)+1, 0x8, 0b1110, 0, 1);

    idt_set_gate(19, (unsigned int) &(isr_handler)+1, 0x8, 0b1111, 0, 1);


    //IRQs
    idt_set_gate(32, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(33, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(34, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(35, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(36, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(37, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(38, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(39, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);

    idt_set_gate(40, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(41, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(42, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(43, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(44, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(45, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(46, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);
    idt_set_gate(47, (uint32_t) &irq_handler, 0x8, 0b1110, 0, 1);

    idt_load();
}
