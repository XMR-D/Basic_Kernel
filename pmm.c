#include "system.h"

struct memblock{
    uint32_t size : 32;
    uint64_t address : 64;
    uint64_t length : 64;
    uint32_t type : 32;
};

struct multibootinfo{
    uint32_t flags : 32;

    uint32_t memlow : 32;
    uint32_t memhigh : 32;
    uint32_t boot_device : 32;

    uint32_t cmdline : 32;
    uint32_t mods_count : 32;
    uint32_t mods_addr : 32;

    uint32_t syms : 32;

    uint32_t mmap_length : 32;
    uint32_t mmap_addr : 32;
}__attribute__((packed));

typedef struct multibootinfo multibootinfo_t;
typedef struct memblock memblock_t;

void Multiboot_log(multibootinfo_t * minfo)
{
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "\n");
    sprintf((unsigned char *) "flags value = %x\n", minfo->flags);
    sprintf((unsigned char *) "memlow value = %x\n", minfo->memlow);
    sprintf((unsigned char *) "memhigh value = %x\n", minfo->memhigh);
    sprintf((unsigned char *) "boot device value = %x\n", minfo->boot_device);
    sprintf((unsigned char *) "cmdline value = %x\n", minfo->cmdline);
    sprintf((unsigned char *) "mods_count value = %x\n", minfo->mods_count);
    sprintf((unsigned char *) "mods_addr value = %x\n", minfo->mods_addr);
    sprintf((unsigned char *) "syms value = %x\n", minfo->syms);
    sprintf((unsigned char *) "mmap length value = %x\n", minfo->mmap_length);
    sprintf((unsigned char *) "mmap addr value = %x\n", minfo->mmap_addr);
}





int get_mmap(multibootinfo_t * minfo)
{
    uint32_t mmap = minfo->mmap_addr;
    uint32_t length = minfo->mmap_length;
    Multiboot_log(minfo);

    int count = 0;

    if(!(minfo->flags >> 6 & 0x1))
    {
        printf((unsigned char *) "invalid memory map !");
        return 1;
    }

    for(uint32_t i = 0; i < length; i += sizeof(memblock_t))
    {
        count += 1;
        memblock_t * block = (memblock_t *) mmap + i;
        sprintf((unsigned char *) "Memory bloc number %u : Start addr = %x || Length = %x || Size: %x || Type = %x\n",
                count, block->address, block->length, block->size, block->type);
    }
    return 0;
}
