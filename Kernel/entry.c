#include "stm32f2xx.h"

uint32_t __initial_sp = 0x20002000;

__asm
void enter_user_mode(void)
{
    // change to user mode
	MRS R0, CONTROL
	ORR R0, #3
	MSR CONTROL, R0

    BX LR
}

__asm
void reset_msp(void)
{
    LDR R0, =0X20020000
	MSR MSP, R0
    BX LR
}

extern void user_task(void *arg);

// the idle task, enter power save mode
void main(void)
{
    reset_msp();
    
    ENTER_CRITICAL();
    
    SysClock_Init();

    SysTick_Init();

    task0_init();
    
    EXIT_CRITICAL();

    enter_user_mode();

    task_create(user_task);

    while(1)
    {
        sleep(0);
    }
}

