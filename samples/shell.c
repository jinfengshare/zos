#include <stdio.h>
#include "types.h"

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

void shell(void *arg)
{
    int ret;
    uint8_t line[64];
    
    while(1)
    {
        printf(">>");

        ret = read_line(line, 64);
        if(-1 == ret)
        {
            continue;
        }

        if(0 == strcmp(line, "ls"))
        {
            printf(". ..\r\n");
        }
        else if(0 == strcmp(line, "pwd"))
        {
            printf("new user ?\r\n");
        }
        else
        {
            printf("no help info now\r\n");
        }
    }
}

