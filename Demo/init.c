#include "task.h"

extern void main(void * arg);
extern void task_uart(void * arg);
extern void task_04(void * arg);
extern void task_05(void * arg);
extern void task_06(void * arg);
extern void task_07(void * arg);
extern void task_08(void * arg);
extern void task_09(void * arg);
extern void task_10(void * arg);
extern void task_11(void * arg);
extern void task_12(void * arg);
extern void task_13(void * arg);
extern void task_14(void * arg);
extern void task_15(void * arg);
extern void task_16(void * arg);

int os_init(void)
{	
	task0_init();
	
	task_create(main);
	task_create(task_uart);
	
	task_create(task_04);
	task_create(task_05);
	task_create(task_06);
	task_create(task_07);
	task_create(task_08);
	task_create(task_09);
	task_create(task_10);
	task_create(task_11);
	task_create(task_12);
	task_create(task_13);
	task_create(task_14);
	task_create(task_15);
	task_create(task_16);
	
	while(1)
	{
		__asm{SVC #0};
	}
}
