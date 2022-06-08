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
static struct idt_gate_descriptor idt[256];

void idt_set_gate(uint8_t num, uint16_t l_o, uint16_t c_s, uint8_t g_t, uint8_t dpl, uint8_t p, uint8_t h_o)
{
    idt[num].lowoffset = l_o;
    idt[num].codeselect = c_s;
    idt[num].reserved = 0;
    idt[num].gatetype = g_t;
    idt[num].always0 = 0;
    idt[num].dpl = dpl;
    idt[num].p = p;
    idt[num].highoffset = h_o;

}

void idt_format()
{
    for(int i = 0; i <= 255; i++)
    {
        idt_set_gate(i, 0, 0, 0, 0, 0, 0x0);
    }
}

void idt_init()
{
    idtpointer.size = (sizeof(struct idt_gate_descriptor)*256)-1;
    idtpointer.idt_adress = (unsigned int) &idt;

    idt_format();
    idt_set_gate(0, 0x0793, 0x8, 0b1111, 0, 1, 0x0001);
    idt_load();
}
