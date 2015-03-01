/*
 * jinfeng, 2014/7/26
 * MXCHIP Co.Ltd.
 */

#include <stdlib.h>
#include <stm32f2xx.h>
#include <ringbuf.h>

#define BUFFERLEN 256

ringbuf_t ringbuffer;
uint8_t rx_buffer[BUFFERLEN];

static void gpio_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void uart_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_DeInit(USART1);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_DMACmd(USART1, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);

    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1, ENABLE);	
}

static void nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );
}

void tty_init(void)
{
    ringbuf_init(&ringbuffer, rx_buffer, BUFFERLEN);
    
	nvic_init();
	uart_init();
	gpio_init();
}

uint8_t tty_read(void)
{
    uint8_t c;
    
    if(0 == ringbuf_get_datalen(&ringbuffer))
    {
        return -1;
    }

    ringbuf_get_data(&ringbuffer, &c, 1);

    return c;
}

void uart_write_byte(uint8_t b)
{
    while (RESET == USART_GetFlagStatus(USART1, USART_FLAG_TXE));
    
    USART_SendData(USART1, (uint16_t)b);
}

void interrupt_uart_add(uint8_t data)
{
    uart_write_byte(data);

    if('\r' == data)
    {
        uart_write_byte('\n');
    }
    
    ringbuf_add(&ringbuffer, &data, 1);
}

