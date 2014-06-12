#include "task.h"

os_tcb_t g_tcb_a;

int init(void)
{
	extern void task_b(void *arg);
	extern task_t g_cur_task;
	
	g_cur_task.stack_top = 0x20010000;
	g_cur_task.stack_size = 1024;	// 1K
	g_cur_task.id = 1;
	
	g_tcb_a.stack_top = 0x20010000;
	g_tcb_a.stack_size = 1024;	// 1K
	g_tcb_a.id = 1;
	
	task_create(task_b);
	
	while(1)
	{
		__asm{SVC #0};
	}
}