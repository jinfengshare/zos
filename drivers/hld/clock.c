#include "stm32f2xx.h"

void SysClock_Init(void)
{
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_WaitForHSEStartUp();

    // AHB Clock
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    // APB2 Clock
    RCC_PCLK2Config(RCC_HCLK_Div2);

    // APB1 Clock
    RCC_PCLK1Config(RCC_HCLK_Div4);

    FLASH_SetLatency(FLASH_Latency_3);
    FLASH_PrefetchBufferCmd(ENABLE);

    RCC_PLLConfig(RCC_PLLSource_HSE, 26, 240, 2, 5);
    RCC_PLLCmd(ENABLE);
    while(SET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY));
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    while(0x08 != RCC_GetSYSCLKSource());

    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
}

