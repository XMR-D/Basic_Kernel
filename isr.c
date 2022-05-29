#include "system.h"

struct cpu;

//TODO: define all ISR here!!, push 0 if the isr do not return a error code 
//then push the n byte for the err(n) error;

void err0(struct cpu * context)
{
    //TODO : (push err_code onto the stack)
}

void err1(struct cpu * context)
{
    //TODO
}

void err2(struct cpu * context)
{
    //TODO
}

void err3(struct cpu * context)
{
    //TODO
}

void err4(struct cpu * context)
{
    //TODO
}

typedef void (*isr_handler)(struct cpu *);

isr_handler jumptable[32] = {err0, err1, err2, err3, err4, err5, err6, err7, err8, err9, err10, err11, err12, err13, err14, err15, err16, err17, err18, err19, err20, err21, err22, err23, err24, err25, err26, err27, err28, err29, err30, err31};

void Isr_handling(struct cpu * context)
{
    jumptable[context->nberr](context);
}
