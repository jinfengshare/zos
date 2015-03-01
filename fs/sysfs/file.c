#include <stdio.h>
#include <stm32f2xx.h>
#include "types.h"

extern uint8_t uart_has_data;
extern uint8_t uart_data;

int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, ch);
    
    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));

    return ch;
}

int fgetc(FILE *stream)
{
    uint8_t data;

    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_RXNE));

    data = (uint8_t)USART_ReceiveData(USART1);

    return data;
}

