#include <task.h>
#include <types.h>

os_tcb_t g_cur_task;

static int g_ready_tasks_index = 1;
os_tcb_t g_ready_tasks[TASK_NUM_MAX];
os_tcb_t g_delay_tasks[TASK_NUM_MAX];
uint32_t g_delay_tasks_wakeup[TASK_NUM_MAX];

os_tcb_t *get_tcb(int tid)
{
	if((tid <0)||(tid >= TASK_NUM_MAX))
	{
		return NULL;
	}
	
	return &g_ready_tasks[tid];
}

os_tcb_t * get_tcb_ex(int tid, os_tcb_t * list)
{
    int i;
    
    if((tid <0)||(tid >= TASK_NUM_MAX))
	{
		return NULL;
	}

    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(tid == list[i].id)
        {
            break;
        }
    }
	
	return &list[i];
}

os_tcb_t *get_curtask_tcb(void)
{
	return &g_cur_task;
}


int get_curtask_id(void)
{
    return g_cur_task.id;
}

int delete_task(int tid, os_tcb_t *list)
{
    int i;

    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(tid == list[i].id)
        {
            memset(&list[i], 0, sizeof(os_tcb_t));

            return 0;
        }
    }

    return -1;
}

int add_task(os_tcb_t *array, os_tcb_t *tcb)
{
    int i;

    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(0 == array[i].id)
        {
            memcpy(&array[i], tcb, sizeof(os_tcb_t));

            return 0;
        }
    }

    return -1;
}

int move_curtask_to_delay(uint32_t time2wakeup)
{
    int i;
    
    add_task(g_delay_tasks, get_curtask_tcb());
    
    delete_task(get_curtask_id(), g_ready_tasks);

    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(get_curtask_id() == g_delay_tasks[i].id)
        {
            break;
        }
    }

    g_delay_tasks_wakeup[i] = systick_get() + time2wakeup;

    return 0;
}

int move_delayed_task_to_readylist(int tid)
{
    int i;
    
    add_task(g_ready_tasks, get_tcb_ex(tid, g_delay_tasks));
    
    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(tid == g_delay_tasks[i].id)
        {
            break;
        }
    }

    g_delay_tasks_wakeup[i] = 0xFFFFFFFF;

    delete_task(tid, g_delay_tasks);

    return 0;
}

void check_delayed_task(void)
{
    int i;

    for(i=0; i<TASK_NUM_MAX; i++)
    {
        if(0xFFFFFFFF == g_delay_tasks_wakeup[i])
        {
            continue;
        }
        
        if(g_delay_tasks_wakeup[i] < systick_get())
        {
            move_delayed_task_to_readylist(g_delay_tasks[i].id);
        }
    }
}

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
int task_create(task_entry *entry)
{
	int i;
	unsigned int stacktop;

	for(i=0; i<TASK_NUM_MAX; i++)
	{
		if(0 == g_ready_tasks[i].id)
		{
			// init this task's stack, we must prepare entry in the stack, which can be auto
			// resumed by processor
			stacktop = g_task_stack_table[i];
			stack_init((const unsigned int*)stacktop, (unsigned int)entry);
			stacktop -= 64;
			
			// ID algorithm, simple and useful
			g_ready_tasks[i].id = i+1;

			// no algorithm
			g_ready_tasks[i].stack_top = stacktop;
			g_ready_tasks[i].stack_size = TASK_STACK_SIZE;

			// no algorithm
			g_ready_tasks[i].priority = 128;
			g_ready_tasks[i].tick_last = 128;

			// return task ID
			return g_ready_tasks[i].id;
		}
	}

	return -1;
}

int os_task_select(void)
{
    int i;
    
    for(i=g_ready_tasks_index; i<TASK_NUM_MAX; i++)
    {
        if(g_ready_tasks[i].id > 0)
        {
            g_ready_tasks_index = i+1;

            // fixed bug!!!
            //return g_ready_tasks[i].id;
            return i;
        }
    }

    for(i=0; i<g_ready_tasks_index; i++)
    {
        if(g_ready_tasks[i].id > 0)
        {
            g_ready_tasks_index = i+1;
            return i;
        }
    }

    return -1;
}

// switch
void os_task_switch(void)
{
	int curid, nextid;
	
	// update curtask TCB
	curid = g_cur_task.id;

	g_ready_tasks[curid-1].stack_top = g_cur_task.stack_top;
	g_ready_tasks[curid-1].priority = g_cur_task.priority;
	g_ready_tasks[curid-1].tick_last = g_cur_task.tick_last;

	nextid = os_task_select();
	
	g_cur_task.id = g_ready_tasks[nextid].id;
	g_cur_task.stack_top = g_ready_tasks[nextid].stack_top;
	g_cur_task.priority = g_ready_tasks[nextid].priority;
	g_cur_task.tick_last = g_ready_tasks[nextid].tick_last;
}

void os_curtask_save(void)
{
    int curid;
	
	// update curtask TCB
	curid = g_cur_task.id;

	g_ready_tasks[curid-1].stack_top = g_cur_task.stack_top;
	g_ready_tasks[curid-1].priority = g_cur_task.priority;
	g_ready_tasks[curid-1].tick_last = g_cur_task.tick_last;
}

void os_switch2next_task(void)
{
    int nextid;
    
    nextid = os_task_select();
	
	g_cur_task.id = g_ready_tasks[nextid].id;
	g_cur_task.stack_top = g_ready_tasks[nextid].stack_top;
	g_cur_task.priority = g_ready_tasks[nextid].priority;
	g_cur_task.tick_last = g_ready_tasks[nextid].tick_last;
}

void task0_init(void)
{
	memset(g_ready_tasks, 0, sizeof(g_ready_tasks));
    memset(g_delay_tasks, 0, sizeof(g_delay_tasks));
    memset(g_delay_tasks_wakeup, 0xFF, sizeof(g_delay_tasks_wakeup));

    g_ready_tasks_index = 1;
	
	g_cur_task.id = 1;
	g_cur_task.priority = 128;
	g_cur_task.stack_size = TASK_STACK_SIZE;
	g_cur_task.stack_top = g_task_stack_table[0];
	g_cur_task.tick_last = 128;

	g_ready_tasks[0].id = 1;
	g_ready_tasks[0].priority = 128;
	g_ready_tasks[0].stack_size = TASK_STACK_SIZE;
	g_ready_tasks[0].stack_top = g_task_stack_table[0];
	g_ready_tasks[0].tick_last = 128;
}

