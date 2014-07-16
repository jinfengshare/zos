#ifndef TASK_H
#define TASK_H

#include "ipc.h"

#define TASK_NUM_MAX	16

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
	// IPC
	
	// Resource related
} os_tcb_t;

typedef void(*task_entry)(void *arg);

// fixed bug
#if 0
int task_create(task_entry *entry);
#else
int task_create(void(*task_entry)(void *arg));
#endif
#endif
