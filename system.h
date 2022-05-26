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

#endif
