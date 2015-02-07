#include "stm32f2xx.h"
#include "core_cm3.h"

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

extern void user_task(void *arg);

extern unsigned int SystemCoreClock;

// the idle task, enter power save mode
void main(void)
{
    SysClock_Init();

    systick_init();
    SysTick_Config(120000);
    
    task0_init();

    enter_user_mode();

    task_create(user_task);

    while(1)
    {
        // do enter sleep mode, set least task wakeup time
        schedule();
    }
}

