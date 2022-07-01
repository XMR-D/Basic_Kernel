#include "system.h"

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) 
    {
        *dp++ = *sp++;
    }
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) 
    {
        *temp++ = val;
    }
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--)
    {
        *temp++ = val;
    }
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++)
    {
        retval++;
    }
    return retval;
}

unsigned char inb (unsigned short _port)
{
    unsigned char rv;
    asm volatile("in %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outb (unsigned short _port, unsigned char _data)
{
    asm volatile("out %1, %0" : : "dN" (_port), "a" (_data));
}



void main()
{
    /* You would add commands after here */

    /* ...and leave this loop in. for(;;);*/

    gdt_install();
    init_video();
    idt_init();
    irq_remap();
    keyboard_handling();

    puts((unsigned char *) "Hello kernel world!\n");

    //division by 0 test : successful !
    //asm volatile("movw $1, %eax; div %eax, %eax");

    for (;;);
}
