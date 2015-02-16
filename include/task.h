#ifndef TASK_H
#define TASK_H

#define TASK_NUM_MAX	16
#define MSG_QUEUE_SIZE	100

#define TASK_STACK_SIZE	1024

typedef struct
{
	/* CPU - Stack */
	unsigned int stack_top;
	unsigned int stack_size;

	/* Task -Info */
	unsigned int id;
	unsigned int priority;	// for scheduler
	unsigned int tick_last;	// for scheduler

	/* Process Control */
	// IPC - Msg Queue
	unsigned char msgqueue[MSG_QUEUE_SIZE];
	unsigned int msgpos;
	
	// Resource related
	
} os_tcb_t;

typedef void(*task_entry)(void *arg);

os_tcb_t *get_tcb(int tid);

int task_create(task_entry *entry);

#endif
