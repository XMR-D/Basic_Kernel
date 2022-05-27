#include "system.h"

//TODO: define all ISR here!!

typedef void (*isr_handler)(void);

isr_handler jumptable[32] = {err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, err15, err16, err17, err18, err19, err20, err21, err22, err23, err24, err25, err26, err27, err28, err29, err30, err31};

void Isr_handler(uint32_t nb)
{
    switch(nb >= 32)
    {
    case 1:
        jumptable[31]();
        break;
    default:
        jumptable[nb]();
        break;
    }
}
