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
"\
help\r\n\
echo\r\n\
ps\r\n\
";

static const char *ps_result_string = 
"\
-----------------------------------------\r\n\
Name            Priority        STATE\r\n\
-----------------------------------------\r\n\
init            0               running\r\n\
user task       0               running\r\n\
shell           1               running\r\n\
-----------------------------------------\r\n\
";

int read_line(uint8_t *buffer, uint32_t len)
{
    uint32_t i = 0;
    char c;
    
    do
    {
        c = getchar();
        buffer[i++] = c;
    } while('\r' != c);

    buffer[i] = 0;

    return i-1;
}

void do_echo(uint8_t *buffer)
{
    printf("%s\r\n", buffer);
}

void do_ps(void)
{
    printf(ps_result_string);
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
        if(ret <= 0)
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
        else if(strstr(buffer, "ps"))
        {
            do_ps();
        }
        else
        {
            printf(help_string);
        }
    }
}

