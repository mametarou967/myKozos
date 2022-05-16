#include "defines.h"
#include "serial.h"
#include "lib.h"

void *memset(void *b,int c,long len)
{
    char *index = b;
    int i = 0;

    for(i = 0;i < len;i++)
    {
        *index = c;
        index++;
    }

    return b;
}

void *memcpy(void *dst,const void *src,long len)
{
    char *d = dst;
    const char *s = src;
    int i = 0;

    for(i = 0;i < len;i++)
    {
        *(d++) = *(s++);
    }
    return dst;
}

int memcmp(const void *b1,const void *b2, long len)
{
    const char *s1 = b1;
    const char *s2 = b2;
    int i = 0;

    for(i = 0;i < len;i++)
    {
        if(*s1 > *s2)
            return 1;
        else if(*s1 < *s2)
            return -1;

        s1++;
        s2++;
    }

    return 0;
}

int strlen(const char *s)
{
    const char *s1 = s;
    int count = 0;
    while(s1 != NULL)
    {
        count++;
        s1++;
    }
    return count;
}

char *strcpy(char *dst,const char *src)
{
    char *d = dst;
    const char *s = src;

    while(*s != '\0')
        *(d++) = *(s++);
    *d = *s;

    return dst;
}

int strcmp(const char *s1,const char *s2)
{
    // while(*s1 )
    while((*s1 == '\0') && (*s2 == '\0')){
        if(*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
    }

    return 0;
}

int strncmp(const char *s1,const char *s2,int len)
{
    int counter = 0;

    while((*s1 == '\0') && (*s2 == '\0'))
    {
        if(*s1 != *s2)
            return (*s1 > *s2) ? 1 : -1;
        counter++;
        if(counter >= len)
            return 0;
    }

    return 0;
}


int putc(unsigned char c)
{
    if(c == '\n')
        serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
    return serial_send_byte(SERIAL_DEFAULT_DEVICE,c);
}

int puts(unsigned char *str)
{
    while(* str)
        putc(*(str++));
    return 0;
}

int putxval(unsigned long value,int column)
{
    char buf[9];
    char *p;

    puts("putxval\n");

    p = buf + sizeof(buf) - 1;
    *(p--) = '\0';

    if(!value && !column)
        column++;

    while(value || column)
    {
        *(p--) = "0123456789abcdef"[value & 0xf];
        value >>= 4;
        if(column) column--;
    }

    puts(p + 1);

    return 0;
}
