/*
 * jinfeng, 2014/7/26
 * MXCHIP Co.Ltd.
 */

#include <stdlib.h>
#include <stm32f2xx.h>
#include <lib/ring.h>
#include "hld_uart.h"

#define UART_BUFFER_LEN 256

// send one by one
static uint8_t send_lock = 0;
static uint8_t tx_buffer[UART_BUFFER_LEN] = {0};

// DMA buffer for recv
static uint16_t dma_recv_len = 1; // attention, inited as one byte
static uint8_t rx_buffer[UART_BUFFER_LEN] = {0};

// device open counter
static uint8_t uart1_open_counter = 0;

// ring buffer manager
static uint8_t rx_dma_update = 0;
static uint8_t pick_lock = 0;
static uint8_t _ring_buffer[UART_BUFFER_LEN] = {0};
static ringbuf_t uart_ringbuf;

// make DMA transfter quickly
static DMA_InitTypeDef DMA_SEND_T;
static DMA_InitTypeDef DMA_RECV_T;

#if 1
// for test
volatile uint32_t rx_datalen = 0;
volatile uint32_t tx_datalen = 0;
volatile uint32_t tx_reallen = 0;
#endif

static void _dma_structure_init(void)
{
	DMA_RECV_T.DMA_PeripheralBaseAddr = ((uint32_t)USART1 + 0x04);
	DMA_RECV_T.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_RECV_T.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_RECV_T.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_RECV_T.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_RECV_T.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_RECV_T.DMA_Mode = DMA_Mode_Circular;
	DMA_RECV_T.DMA_Priority = DMA_Priority_High;
	DMA_RECV_T.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_RECV_T.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_RECV_T.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_RECV_T.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_RECV_T.DMA_Channel = DMA_Channel_4;

	DMA_SEND_T.DMA_PeripheralBaseAddr = ((uint32_t)USART1 + 0x04);
	DMA_SEND_T.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_SEND_T.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_SEND_T.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_SEND_T.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_SEND_T.DMA_Mode = DMA_Mode_Normal;
	DMA_SEND_T.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_SEND_T.DMA_FIFOMode = DMA_FIFOMode_Disable; // ?
	DMA_SEND_T.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_SEND_T.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_SEND_T.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_SEND_T.DMA_Channel = DMA_Channel_4;
	DMA_SEND_T.DMA_DIR = DMA_DIR_MemoryToPeripheral;
}

static void _uart_ringbuf_init(void)
{
	uart_ringbuf.buffer = _ring_buffer;
	uart_ringbuf.buflen = 10;
	uart_ringbuf.attr = RING_OVERWRITE;

	ringbuf_init(&uart_ringbuf);
}

static void _gpio_init(void)
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

static void _uart_init(void)
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
	
	USART_Cmd(USART1, ENABLE);	
}

static void _nvic_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x6;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );
}


static void _dma_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_DeInit(DMA2_Stream2);
	DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);

	DMA_RECV_T.DMA_Memory0BaseAddr = (uint32_t)rx_buffer;
	DMA_RECV_T.DMA_BufferSize = dma_recv_len;

	DMA_Init(DMA2_Stream2, &DMA_RECV_T);

	DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE );

	DMA_Cmd(DMA2_Stream2, ENABLE);
}

void hal_uart1_init(void)
{
	_uart_ringbuf_init();
	_dma_structure_init();
	
	_nvic_init();
	_uart_init();
	_dma_init();
	_gpio_init();
}

static void dma_set_recvlen(unsigned int len)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);

	DMA_DeInit(DMA2_Stream2);
	DMA_ClearFlag(DMA2_Stream2, DMA_FLAG_TCIF2);

	DMA_RECV_T.DMA_BufferSize = len;

	DMA_Init(DMA2_Stream2, &DMA_RECV_T);

	DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE );

	DMA_Cmd(DMA2_Stream2, ENABLE);
}

int hal_uart1_open(void)
{
	uart1_open_counter++;
	return 0;
}

int hal_uart1_close(void)
{
	if(0 == uart1_open_counter)
	{
		return -1;
	}
	uart1_open_counter--;
  
  return 0;
}

int hal_uart1_ctrl(int option, void *value, unsigned int optlen)
{
	switch(option)
	{
	case DMA_RECV_SIZE:
		if(optlen == sizeof(unsigned int))
		{
    		dma_recv_len = (unsigned int)value;
			dma_set_recvlen(dma_recv_len);
  			return 0;
		}
		else
  		{
    		return -1;
  		}
  	case RECV_DATA_TIMESTAMP:
	    break;
	default:
		break;
	}
  
  return 0;
}

int hal_uart1_write(unsigned char *buffer, unsigned int len)
{	
	tx_datalen += len;
	
	if((NULL == buffer)||(0 == len)||(len>UART_BUFFER_LEN))
	{
		return 0;
	}
	
	if(send_lock)
	{
		return 0; // sync write 0 byte
	}
	send_lock = 1;
	
	tx_reallen += len;

	memcpy(tx_buffer, buffer, len);

	DMA_DeInit(DMA2_Stream7);

	DMA_SEND_T.DMA_Memory0BaseAddr = (uint32_t)tx_buffer;
	DMA_SEND_T.DMA_BufferSize = len;

	DMA_Init(DMA2_Stream7, &DMA_SEND_T);

	USART_ClearFlag(USART1, USART_FLAG_TC);
	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE );

	DMA_Cmd(DMA2_Stream7, ENABLE);
	
	return len;
}

// has buffer manage
int hal_uart1_read(unsigned char *buffer, unsigned int len)
{	
	int ret;
	
	// parameter check
	if((NULL==buffer)||(0==len))
	{
		return 0;
	}

	pick_lock = 1;

	ret = ringbuf_pick(&uart_ringbuf, buffer, len);

	if(rx_dma_update)
	{
		if(rx_dma_update > 1)
		{
			rx_dma_update = 0;
		}
		rx_dma_update--;
		ringbuf_put(&uart_ringbuf, rx_buffer, dma_recv_len);
	}
	
	return ret;
}

void interrupt_usart1_send_complete(void)
{
	send_lock = 0;
}
void interrupt_usart1_add(void)
{
	rx_datalen += dma_recv_len;
	
	// if reading, pick after read
	if(pick_lock)
	{
		rx_dma_update++;
		return;
	}
	else
	{
		// maybe here fail
		ringbuf_put(&uart_ringbuf, rx_buffer, dma_recv_len);
	}
}

