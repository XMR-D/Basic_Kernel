#ifndef __SYSTEM_H
#define __SYSTEM_H
#include <stdint.h>

typedef int size_t;

//main fncts
extern void *memcpy(void *dest, const void *src, size_t count);
extern void *memset(void *dest, char val, size_t count);
extern unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count);
extern size_t strlen(const char *str);
extern unsigned char inportb (unsigned short _port);
extern void outportb (unsigned short _port, unsigned char _data);

//Screen and print functions
extern void cls();
extern void putch(unsigned char c);
extern void puts(unsigned char *str);
extern void putint(int nb);
extern void puthex(int nb);
extern void settextcolor(unsigned char forecolor, unsigned char backcolor);
extern void printf(unsigned char *str, ...);
extern void init_video();

//GDT structs and functions
extern void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
extern void gdt_install();

//IDT structs and functions

extern void idt_set_descriptor(uint32_t baseadress, uint16_t segment, uint8_t flags, uint8_t index);
extern void idt_init();

//ISRS structs and functions

extern uint32_t err0();
extern uint32_t err1();
extern uint32_t err2();
extern uint32_t err3();
extern uint32_t err4();
extern uint32_t err5();
extern uint32_t err6();
extern uint32_t err7();
extern uint32_t err8();
extern uint32_t err9();
extern uint32_t err10();
extern uint32_t err11();
extern uint32_t err12();
extern uint32_t err13();
extern uint32_t err14();
extern uint32_t reserved(); //Unknown Interrupt exception //
extern uint32_t err16();    //Coprocessor Fault exception //
extern uint32_t err17();    //Alignment Check exception   //
extern uint32_t err18();    //machine check exception     //




#endif
