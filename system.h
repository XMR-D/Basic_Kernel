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
extern void gdt_set_gate(int num, uint16_t lowlimit, uint8_t highlimit, uint16_t lowbase, uint8_t middlebase, uint16_t highbase, uint8_t a, uint8_t rw, uint8_t dc, uint8_t e, uint8_t s, uint8_t dpl, uint8_t p, uint8_t g, uint8_t db, uint8_t l);
extern void gdt_install();

//IDT structs and functions

extern void idt_set_gate(uint8_t num, uint16_t l_o, uint16_t c_s, uint8_t g_t, uint8_t dpl, uint8_t p, uint8_t h_o);

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
extern void reserved(); //Unknown Interrupt exception //
extern void err16();    //Coprocessor Fault exception //
extern void err17();    //Alignment Check exception   //
extern void err18();    //machine check exception     //




#endif
