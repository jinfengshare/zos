#include <stdio.h>
#include "types.h"

static const char *welcome_string =
"\r\n\
*-----------------------------------------------*\r\n\
*               RTOS Demo                       *\r\n\
*                                               *\r\n\
*           Designed by Jinfeng Zhuang          *\r\n\
*              Copyright 2014, 2015             *\r\n\
*                                               *\r\n\
*-----------------------------------------------*\r\n\
";

static const char *help_string =
"\r\n\
help\r\n\
echo\r\n\
";

int read_line(uint8_t *buffer, uint32_t len)
{
    uint32_t i = 0;
    char c;
    
    do
    {
        c = getchar();
        buffer[i++] = c;
    } while('\n' != c);

    buffer[i] = 0;

    return i;
}

void do_echo(uint8_t *buffer)
{
    printf("%s\r\n", buffer);
}

void shell(void *arg)
{
    int ret;
    uint8_t buffer[32];

    printf(welcome_string);

    while(1)
    {
        printf("$ ");
        memset(buffer, 0, 32);
        ret = read_line(buffer, 32);
        if(-1 == ret)
        {
            continue;
        }

        if(strstr(buffer, "help"))
        {
            printf(help_string);
        }
        else if(strstr(buffer, "echo"))
        {
            do_echo(&buffer[5]);
        }
        else
        {
            printf(help_string);
        }
    }
}

