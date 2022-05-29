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
extern void err15(); //Unknown Interrupt exception //
extern void err16(); //Coprocessor Fault exception //
extern void err17(); //Alignment Check exception   //
extern void err18(); //machine check exception     //

extern void err19(); //Reserved------
extern void err20();
extern void err21();
extern void err22();
extern void err23();
extern void err24();
extern void err25();
extern void err26();
extern void err27();
extern void err28();
extern void err29();
extern void err30();
extern void err31();
extern void err32();

extern void Isr_handler(uint32_t nb);

extern struct {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; //pusha
    uint32_t nberr, err_code; //interrupt code
    uint32_t gs, fs, es, ds, ss; //push ds,es,fs,gs,ss
}cpu;

#endif
