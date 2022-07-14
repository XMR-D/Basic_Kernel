#include "system.h"

typedef struct memblock{
    uint32_t addr_high : 32;
    uint32_t addr_low : 32;
    uint32_t len_high : 32;
    uint32_t len_low : 32;
    uint32_t type : 32;
}__attribute__((packed)) memblock_t;

typedef struct multibootinfo{
    uint32_t flags : 32;

    uint32_t memlow : 32;
    uint32_t memhigh : 32;
    uint32_t boot_device : 32;

    uint32_t cmdline : 32;
    uint32_t mods_count : 32;
    uint32_t mods_addr : 32;

    uint32_t syms : 32;
    uint32_t syms2 : 32;
    uint32_t syms3 : 32;
    uint32_t syms4 : 32;

    uint32_t mmap_length : 32;
    uint32_t mmap_addr : 32;
}__attribute__((packed)) multibootinfo_t;


void Memory_log(multibootinfo_t *  minfo)
{
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "_______________Multiboot info struct log________________\n");
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "flags value = %x\n", minfo->flags);
    asm volatile("xchg %bx, %bx");
    sprintf((unsigned char *) "mem_lower / mem_upper : %x / %x\n", minfo->memlow, minfo->memhigh);
    sprintf((unsigned char *) "mmap length value = %x\n", minfo->mmap_length);
    sprintf((unsigned char *) "mmap addr value = %x\n", minfo->mmap_addr);
    sprintf((unsigned char *) "______________Memory Bloc 1 log_________________________\n");

    multibootinfo_t * mbi = (uint32_t) minfo;
    memblock_t * block = (uint32_t) mbi->mmap_addr;

    sprintf((unsigned char *) "block base addr : %x%x\nblock length : %x%x\nblock type: %x\n",block->addr_high, block->addr_low,  block->len_high, block->len_low, block->type);



}


int get_mmap(multibootinfo_t * minfo)
{
    uint32_t mmap = minfo->mmap_addr;
    uint32_t length = minfo->mmap_length;
    Memory_log(minfo);

    /*int count = 0;

    if(!(minfo->flags >> 6 & 0x1))
    {
        printf((unsigned char *) "invalid memory map !");
        return 1;
    }

    memblock_t * block = (memblock_t *) mmap;

    for(uint32_t i = 0; i < length; i += 1)
    {
        count += 1;
        sprintf((unsigned char *) "Memory bloc number %u : Start addr = %x%x || Length = %x%x || Type = %x\n",
               count , block->addr_high, block->addr_low, block->len_high, block->len_low, block->type);
        block = (mmap+sizeof(memblock_t *));
        mmap = &block;
    }*/
    return 0;
}
