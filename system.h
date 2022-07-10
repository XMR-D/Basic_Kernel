#ifndef __SYSTEM_H
#define __SYSTEM_H
#include <stdint.h>
//type and misc definitions
typedef int size_t;

//main fncts
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inb (unsigned short _port);
extern void outb (unsigned short _port, unsigned char _data);

//Screen and print functions and Driver series functions


extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void putint(int nb);
extern void puthex(int nb);
extern void sputint(int nb);
extern void sputhex(int nb);
extern void sputs(unsigned char *str);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void printf(unsigned char *str, ...);
extern void sprintf(unsigned char *str, ...);
extern void keyboard_handling();
extern void init_video();

//GDT structs and functions
extern void gdt_set_gate(int num, uint16_t lowlimit, uint8_t highlimit, uint16_t lowbase, uint8_t middlebase, uint16_t highbase, uint8_t a, uint8_t rw, uint8_t dc, uint8_t e, uint8_t s, uint8_t dpl, uint8_t p, uint8_t g, uint8_t db, uint8_t l);
extern void gdt_install();

//IDT structs and functions

extern void idt_set_gate(uint8_t num, uint32_t o, uint16_t c_s, uint8_t g_t, uint8_t dpl, uint8_t p);

extern void idt_init();

//ISRS structs and functions

extern void err0();
extern void err1();
extern void err2();
extern void err3();
extern void err4();
extern void err5();
extern void err6();
extern void err7();
extern void err8();
extern void err9();
extern void err10();
extern void err11();
extern void err12();
extern void err13();
extern void err14();
extern void reserved();
extern void err16();
extern void err17();
extern void err18();

extern void change_args(uint32_t nberr, uint32_t code);

//IRQs and function

extern void irqe0();
extern void irqe1();
extern void irqe2();
extern void irqe3();
extern void irqe4();
extern void irqe5();
extern void irqe6();
extern void irqe7();
extern void irqe8();
extern void irqe10();
extern void irqe11();
extern void irqe12();
extern void irqe13();
extern void irqe14();
extern void irqe15();

extern void Irq_remap();

//PHysical memory manager functions

//extern void get_mmap(multibootinfo * minfo);

#endif
