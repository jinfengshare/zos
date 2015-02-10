#include <stm32f2xx.h>

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	systick_irq();
}

//-----------------------------------------
// USART1 related
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_IDLE) == SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_IDLE);
	}
}
// for recv complete
void DMA2_Stream2_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream2, DMA_IT_TCIF2))
	{
		DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);
	}
}
// for send complete
void DMA2_Stream7_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream7, DMA_IT_TCIF7))
	{
		DMA_ClearITPendingBit(DMA2_Stream7, DMA_IT_TCIF7);
	}
}
//-----------------------------------------
