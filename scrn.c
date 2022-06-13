#include "system.h"
#include <stdarg.h>

/* These define our textpointer, our background and foreground
*  colors (attributes), and x and y cursor coordinates */
unsigned short *textmemptr;
int attrib = 0x0F;
int csr_x = 0, csr_y = 0;

/* Scrolls the screen */
void scroll(void)
{
    unsigned blank, temp;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (attrib << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(csr_y >= 25)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - 25 + 1;
        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

/* Updates the hardware cursor: the little blinking line
*  on the screen under the last character pressed! */
void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
    unsigned blank;
    int i;

    /* Again, we need the 'short' that will be used to
    *  represent a space with color */
    blank = 0x20 | (attrib << 8);

    /* Sets the entire screen to spaces in our current
    *  color */
    for(i = 0; i < 25; i++)
        memsetw(textmemptr + i * 80, blank, 80);

    /* Update out virtual cursor, and then move the
    *  hardware cursor */
    csr_x = 0;
    csr_y = 0;
    move_csr();
}

/* Puts a single character on the screen */
void putch(unsigned char c)
{
    unsigned short *where;
    unsigned att = attrib << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;	/* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}

/* Uses the above routine to output a string... */
void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen((const char *)text); i++)
    {
        putch(text[i]);
    }
}

void putint(int nb)
{
    int count = 1;
    int x = 0;
    int saved = nb;
    if(nb < 0)
    {
        putch((unsigned char) '-');
        nb *= -1;
    }
    while(nb > 0)
    {
        nb /= 10;
        count *= 10;
    }
    while(count > 0)
    {
        if(x >= 1)
        {
            putch((saved/count) + 48);
            saved -= (saved/count)*count;
            count /= 10;
        }
        else
        {
            x += 1;
            count /= 10;
        }
    }
}

void puthex(int nb)
{
    int temp = 0;
    char * arr = "00000000";
    int i = 0;
    while(nb > 0)
    {
        temp = nb % 16;
        if(temp < 10)
        {
            arr[i] = temp+48;
            i += 1;
        }
        else
        {
            arr[i] = temp+55;
            i += 1;
        }
        nb /= 16;
    }
    
    for(i = strlen(arr); i >= 0; i--)
        putch(arr[i]);
}

/* Sets the forecolor and backcolor that we will use */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

/* print a string on the terminal, format (= %c, %s, %d, %u, %x) */
void printf(unsigned char * str, ...)
{
    int i = 0;
    va_list ap;

    /* Set our constant for formatting string */
    int chara;
    char * string;
    int inte;
    int hex;
    unsigned int unsi;
    va_start(ap, str);


    while(str[i] != '\0')
    {
        if(str[i] == '%')
        {
            i += 1;
            switch(str[i])
            {
                case 'c':
                    chara = va_arg(ap, int);
                    putch(chara);
                    break;
                case 's':
                    string = va_arg(ap, char *);
                    puts((unsigned char *) string);
                    break;
                case 'd':
                    inte = va_arg(ap, int);
                    putint(inte);
                    break;
                case 'u':
                    unsi = va_arg(ap, unsigned int);
                    putint(unsi);
                    break;
                case 'x':
                    hex = va_arg(ap, int);
                    puthex(hex);
                    break;
                default:
                    putch(str[i]);
            }
            i += 1;
        }
        else
        {
            putch(str[i]);
            i += 1;
        }

    }
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
    textmemptr = (unsigned short *) 0xB8000;
    cls();
}
		
