#include "system.h"

void Memory_log(multibootinfo_t *  minfo)
{
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "_______________Multiboot info struct log________________\n");
    sprintf((unsigned char *) "struct adress : %x\n", &(minfo));
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "struct value : %x\n", minfo);
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "flags value = %x\n", minfo->flags);
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "mem_lower / mem_upper : %x / %x\n", minfo->memlow, minfo->memhigh);
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "mmap length value = %x\n", minfo->mmap_length);
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "mmap addr value = %x\n", minfo->mmap_addr);
}

uint32_t * get_block(uint32_t * block_addr)
{
    memblock_t result;

    result.size = *(block_addr);
    sprintf((unsigned char *) "%x\n", result.size);

    result.addr_high = *(block_addr + 1);

    result.addr_low = *(block_addr + 2);
    sprintf((unsigned char *) "%x%x\n", result.addr_low, result.addr_high);

    result.len_low = *(block_addr + 3);

    result.len_high =  *(block_addr + 4);
    sprintf((unsigned char *) "%x%x\n", result.len_high, result.len_low);

    result.type = *(block_addr + 5);
    sprintf((unsigned char *) "%u\n", result.type);

    return (block_addr + 6);
}


int get_mmap(multibootinfo_t * minfo)
{
    Memory_log(minfo);
    uint32_t count = 0;

    uint32_t * add = get_block((uint32_t *) minfo->mmap_addr);

    sprintf((unsigned char *) "\n");


    for(; count < 10 ;)
    {
        sprintf((unsigned char *) "memory block number : %u\n", count);
        add = get_block(add);
        sprintf((unsigned char *) "\n");
        count++;
    }

    return 0;
}
