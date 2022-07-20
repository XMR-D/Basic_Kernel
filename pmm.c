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

memblock_t get_block(uint32_t * block_addr)
{
    memblock_t result;

    result.size = *(block_addr);
    sprintf("%x\n", result.size);
    if(result.size == 0x14)
        printf("01\n");

    result.addr_high = *(block_addr +1);
    sprintf("%x\n", result.addr_high);
    if(result.addr_high == 0x0)
        printf("02\n");

    result.addr_low = *(block_addr + 2);
    sprintf("%x\n", result.addr_low);
    if(result.addr_low == 0x0)
        printf("03\n");

    result.len_low = *(block_addr + 3);
    sprintf("%x\n", result.len_low);
    if(result.len_low == 0x9fc00)
        printf("04\n");

    result.len_high =  *(block_addr + 4);
    sprintf("%x\n", result.len_high);
    if(result.len_high == 0x0)
        printf("05\n");

    result.type = *(block_addr + 5);
    sprintf("%x\n", result.type);
    if(result.type == 0x1)
        printf("06\n");

    return result;
}


int get_mmap(uint32_t address, multibootinfo_t * minfo)
{
    //Memory_log(minfo);

    memblock_t block = get_block(minfo->mmap_addr);

    /*sprintf("%x\n%x\n%x\n%x\n%x\n%x\n", block.size, block.addr_high, block.addr_low, block.len_high, block.len_low, block.type);*/

    return 0;
}
