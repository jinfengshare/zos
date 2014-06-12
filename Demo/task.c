#include "task.h"

os_tcb_t g_cur_task;

os_tcb_t g_tcb_b;

void task_create(task_entry *entry)
{
	unsigned int *stack_top;
	
	stack_top = (unsigned int*)(0x20010000-1024);
	
	// for first ret from SVC, task need stack to return
	*stack_top-- = 0;	// xPSR
	*stack_top-- = (unsigned int)entry;	// PC
	*stack_top-- = 0;	// LR
	*stack_top-- = 0;	// R12
	*stack_top-- = 0;	// R3
	*stack_top-- = 0;	// R2
	*stack_top-- = 0;	// R1
	*stack_top-- = 0;	// R0
	
	*stack_top-- = 0;	// R11
	*stack_top-- = 0;	// R10
	*stack_top-- = 0;	// R9
	*stack_top-- = 0;	// R8
	*stack_top-- = 0;	// R7
	*stack_top-- = 0;	// R6
	*stack_top-- = 0;	// R5
	*stack_top-- = 0;	// R4
	
	g_tcb_b.stack_top = 0x20010000-1024-4*16 + 4;
	g_tcb_b.stack_size = 1024;
	g_tcb_b.id = 2;
}
