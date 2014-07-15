#include "task.h"

os_tcb_t g_cur_task;

os_tcb_t g_tcb_array[TASK_NUM_MAX];

// as we should push 8 4-byte registers into task stack which be inited.
const unsigned int g_task_stack_table[TASK_NUM_MAX] =
{
	0x20010000,
	0x2000FC00,
	0x2000F800,
	0x2000F400,
	
	0x2000F000,
	0x2000EC00,
	0x2000E800,
	0x2000E400,
	
	0x2000E000,
	0x2000DC00,
	0x2000D800,
	0x2000D400,

	0x2000D000,
	0x2000CC00,
	0x2000C800,
	0x2000C400,
};

// KISS
static void stack_init(const unsigned int *stacktop, unsigned int entry)
{
	unsigned int *tmp = (unsigned int *)stacktop;

	// fixed bug: example, *0x20010000 = 0
	// means: 0x20010000 - 0x200010004 has data 0
	// so as we push, we should dec address first
	// PUSH => address--, [address] = data
	tmp--;
	
	*tmp-- = 0x01000000;	// xPSR // fixed bug, which cause INVSTATE exception
							// then cause hard fault
							// force state to thumb mode
	*tmp-- = entry;	// PC
	*tmp-- = 0;	// LR
	*tmp-- = 0;	// R12
	*tmp-- = 0;	// R3
	*tmp-- = 0;	// R2
	*tmp-- = 0;	// R1
	*tmp-- = 0;	// R0
	*tmp-- = 0;	// R11
	*tmp-- = 0;	// R10
	*tmp-- = 0;	// R9
	*tmp-- = 0;	// R8
	*tmp-- = 0;	// R7
	*tmp-- = 0;	// R6
	*tmp-- = 0;	// R5
	*tmp-- = 0;	// R4
}

// if not enough space, return -1
int task_create(void(*task_entry)(void *arg))
{
	int i;
	unsigned int stacktop;

	for(i=0; i<TASK_NUM_MAX; i++)
	{
		if(0 == g_tcb_array[i].id)
		{
			// init this task's stack, we must prepare entry in the stack, which can be auto
			// resumed by processor
			stacktop = g_task_stack_table[i];
			stack_init((const unsigned int*)stacktop, (unsigned int)task_entry);
			stacktop -= 64;
			
			// ID algorithm, simple and useful
			g_tcb_array[i].id = i+1;

			// no algorithm
			g_tcb_array[i].stack_top = stacktop;
			g_tcb_array[i].stack_size = TASK_STACK_SIZE;

			// no algorithm
			g_tcb_array[i].priority = 128;
			g_tcb_array[i].tick_last = 128;

			// return task ID
			return g_tcb_array[i].id;
		}
	}

	return -1;
}

// return task ID
int os_task_select(void)
{
	int i;

	int curID;

	int startIdx;

	curID = g_cur_task.id;

 	// get current task index
	for(i=0; i<TASK_NUM_MAX; i++)
	{
		if(curID == g_tcb_array[i].id)
		{
			startIdx = i;
			break;
		}
	}

	// fixed bug: startIdx+1
	startIdx += 1;
	
	// get next task ID based on index
	for(i=startIdx; i<TASK_NUM_MAX; i++)
	{
		if(g_tcb_array[i].id > 0)
		{
			return g_tcb_array[i].id;
		}
	}
	for(i=0; i<startIdx; i++)
	{
		if(g_tcb_array[i].id > 0)
		{
			return g_tcb_array[i].id;
		}
	}

	// if not found, means just task 0 exists in this system
	return g_cur_task.id;
}

// switch
void os_task_switch(void)
{
	int curid, nextid;
	
	// update curtask TCB
	curid = g_cur_task.id;

	g_tcb_array[curid-1].stack_top = g_cur_task.stack_top;
	g_tcb_array[curid-1].priority = g_cur_task.priority;
	g_tcb_array[curid-1].tick_last = g_cur_task.tick_last;

	nextid = os_task_select();
	
	g_cur_task.id = g_tcb_array[nextid-1].id;
	g_cur_task.stack_top = g_tcb_array[nextid-1].stack_top;
	g_cur_task.priority = g_tcb_array[nextid-1].priority;
	g_cur_task.tick_last = g_tcb_array[nextid-1].tick_last;
}

void task0_init(void)
{
	memset(g_tcb_array, 0, sizeof(g_tcb_array));
	
	g_cur_task.id = 1;
	g_cur_task.priority = 128;
	g_cur_task.stack_size = TASK_STACK_SIZE;
	g_cur_task.stack_top = g_task_stack_table[0];
	g_cur_task.tick_last = 128;

	g_tcb_array[0].id = 1;
	g_tcb_array[0].priority = 128;
	g_tcb_array[0].stack_size = TASK_STACK_SIZE;
	g_tcb_array[0].stack_top = g_task_stack_table[0];
	g_tcb_array[0].tick_last = 128;
}

