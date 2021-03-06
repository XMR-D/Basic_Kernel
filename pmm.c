#include "system.h"

void Multiboot_log(multibootinfo_t *  minfo)
{
    sprintf((unsigned char *) "_______________Multiboot info struct log________________\n");
    sprintf((unsigned char *) "multiboot info structure is at : %x\n", &minfo);
    sprintf((unsigned char *) "flags value = %x\n", minfo->flags);
    sprintf((unsigned char *) "mem_lower / mem_upper : %x / %x\n", minfo->memhigh, minfo->memlow);
    sprintf((unsigned char *) "mmap length value = %x\n", minfo->mmap_length);
    sprintf((unsigned char *) "mmap addr value = %x\n", minfo->mmap_addr); 
}

uint64_t bitmaplen;
uint8_t * bitm;

void Bitmaplog(uint64_t nbpages)
{
    uint64_t c = 0;
    for(uint64_t i = 0; i < (nbpages / 8); i++)
    {
        if(c == 10)
        {
            sprintf((unsigned char *) "%b\n", bitm[i]);
            c -= 10;
        }
        else
        {
            sprintf((unsigned char *) "%b", bitm[i]);
            c += 1;
        }
    }
    sprintf("\n");
}

uint8_t * get_mmap(multibootinfo_t * mbd)
{
    Multiboot_log(mbd);
    uint8_t c = 0;
    uint32_t saved = 0;
    uint32_t i;
    uint64_t length;
    uint64_t nbpages = 0;

    for(i = 0; i < mbd->mmap_length;
        i += sizeof(memblock_t))
    {
        memblock_t* mmmt = (memblock_t *) (mbd->mmap_addr + i);

        sprintf((unsigned char *) "Start Addr: %x%x | Length: %x%x | Size: %x | Type: %d\n",
            mmmt->addr_high, mmmt->addr_low, mmmt->len_high, mmmt->len_low, mmmt->size, mmmt->type);

        if(mmmt->type == 1)
        {
            if(c == 0)
            {
                saved = mmmt->addr_low;
                c += 1;
            }
            length = ((uint64_t) (mmmt->len_high << 8)) + ((uint64_t) mmmt->len_low);
            nbpages += (length / 0x1000);
            sprintf((unsigned char *) "pages in this block = %d\n", (length/0x1000));
        }
    }


    sprintf((unsigned char *) "total available pages : %d\n", nbpages);
    sprintf((unsigned char *) "creating appropriate bitmap....\n");

    uint8_t bitmap[(nbpages/8)];

    bitm = (uint8_t *) bitmap;
    bitmaplen = (nbpages/8);

    for(uint64_t j = 0; j <= bitmaplen; j++)
    {
        bitm[i] = 0b00000000;
    }

    sprintf((unsigned char *) "bitmap stored at adress = %x\n", saved);

    Bitmaplog(80);

}

uint8_t allocate(uint64_t i)
{
    uint8_t c = 128;
    uint8_t saved = bitm[i];

    if(bitm[i] == 0)
    {
        bitm[i] = 0b10000000;
        return 0;
    }
    while(saved > 0)
    {
        if((saved && 0b10000000) == 0)
        {
            bitm[i] = bitm[i] | c;
            return 0;
        }
        else
        {
            saved = saved << 1;
            c /= 2;
        }
    }

}

uint32_t alloc(void)
{
   for(uint64_t i = 0; ;i++)
   {
       if(bitm[i] != 1)
       {
           allocate(i);
       }
   }
}

