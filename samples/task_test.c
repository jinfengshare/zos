#include "stm32f2xx.h"

extern void shell(void *arg);

void LED_Init()
{
    GPIO_InitTypeDef   GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void LED_Toggle(void)
{
    GPIO_ToggleBits(GPIOB, GPIO_Pin_1);
}

void user_task(void *arg)
{
    debug_init();

    LED_Init();

    task_create(shell);
    
    while(1)
    {
        sleep(1000);
        
        LED_Toggle();
    }
}

