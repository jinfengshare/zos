#ifndef TASK_H
#define TASK_H

typedef struct
{
	unsigned int stack_top;
	unsigned int stack_size;
	
	unsigned int id;
} os_tcb_t;

typedef void(*task_entry)(void *arg);

#endif