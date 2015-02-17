#include <stm32f2xx.h>

void hard_fault_handler_c(unsigned int *hardfault_args)
{
    unsigned int stacked_r0;
    unsigned int stacked_r1;
    unsigned int stacked_r2;
    unsigned int stacked_r3;
    unsigned int stacked_r12;
    unsigned int stacked_lr;
    unsigned int stacked_pc;
    unsigned int stacked_psr;

    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);

    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    printf("\r\n\r\n[Hard fault handler - all numbers in hex]\r\n");
    printf("R0 = 0x%08X\r\n", stacked_r0);
    printf("R1 = 0x%08X\r\n", stacked_r1);
    printf("R2 = 0x%08X\r\n", stacked_r2);
    printf("R3 = 0x%08X\r\n", stacked_r3);
    printf("R12 = 0x%08X\r\n", stacked_r12);
    printf("LR [R14] = 0x%08X  subroutine call return address\r\n", stacked_lr);
    printf("PC [R15] = 0x%08X  program counter\r\n", stacked_pc);
    printf("PSR = 0x%08X\r\n", stacked_psr);
    printf("BFAR = 0x%08X\r\n", (*((volatile unsigned long *)(0xE000ED38))));
    printf("CFSR = 0x%08X\r\n", (*((volatile unsigned long *)(0xE000ED28))));
    printf("HFSR = 0x%08X\r\n", (*((volatile unsigned long *)(0xE000ED2C))));
    printf("DFSR = 0x%08X\r\n", (*((volatile unsigned long *)(0xE000ED30))));
    printf("AFSR = 0x%08X\r\n", (*((volatile unsigned long *)(0xE000ED3C))));
    printf("SCB_SHCSR = 0x%08X\r\n", SCB->SHCSR);

    while (1);
}

void NMI_Handler(void)
{
}

void SVC_Handler(void)
{
    svc_irq();
}

void PendSV_Handler(void)
{
    pendsv_irq();
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
