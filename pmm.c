#include "system.h"

uint8_t * pages[1310];

void Multiboot_log(multibootinfo_t *  minfo)
{
    sprintf((unsigned char *) "_______________Multiboot info struct log________________\n");
    sprintf((unsigned char *) "flags value = %x\n", minfo->flags);
    sprintf((unsigned char *) "mem_lower / mem_upper : %x / %x\n", minfo->memhigh, minfo->memlow);
    sprintf((unsigned char *) "mmap length value = %x\n", minfo->mmap_length);
    sprintf((unsigned char *) "mmap addr value = %x\n", minfo->mmap_addr); 
}

uint32_t * get_block(uint32_t count, uint32_t * block_addr)
{
    memblock_t result;
    sprintf((unsigned char *) "memory map block %u : ", count);

    result.size = *(block_addr);
    sprintf((unsigned char *) "Size = %x ||", result.size);

    result.addr_high = *(block_addr + 1);

    result.addr_low = *(block_addr + 2);
    sprintf((unsigned char *) " base_address (64_bit) = %x%x ||", result.addr_low, result.addr_high);

    result.len_low = *(block_addr + 3);

    result.len_high =  *(block_addr + 4);
    sprintf((unsigned char *) " length = %x%x ||", result.len_high, result.len_low);

    result.type = *(block_addr + 5);
    sprintf((unsigned char *) " type = %u.", result.type);

    return (block_addr + 6);
}


uint32_t get_mmap(multibootinfo_t * minfo)
{
    Multiboot_log(minfo);
    multibootinfo_t * m = minfo;
    uint32_t count = 0;
    uint32_t nbpages = 0;
    uint64_t length = 0;

    uint32_t * add = (uint32_t *) m->mmap_addr;


    count++;
    sprintf((unsigned char *) "\n");
    while(*(add) != 0)
    {
        length = *(add + 3);
        if(*(add + 5) == 1)
        {
            sprintf("length = %x\n", length);
            nbpages += (length / 0x1000);
            sprintf("pages = %u\n", nbpages);
        }
        add = get_block(count, add);
        sprintf((unsigned char *) "\n");
        count++;
    }

    sprintf((unsigned char *) "number of possible pages in physical memory : %u\n", nbpages);
    sprintf((unsigned char *) "creating appropriate bitmap....\n");

    return 0;
}

uint8_t get_free_page(void)
{
   //TODO 
}


