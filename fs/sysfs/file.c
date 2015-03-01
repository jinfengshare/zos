#include <stdio.h>
#include <stm32f2xx.h>
#include "types.h"

extern uint8_t uart_has_data;
extern uint8_t uart_data;

int fputc(int ch, FILE *f)
{
    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));

    USART_SendData(USART1, ch);

    return ch;
}

int fgetc(FILE *stream)
{
    uint8_t data;

    do
    {
        data = tty_read();
    } while(0xFF == data);

    return data;
}

