#ifndef IPC_H
#define IPC_H

#include <task.h>

typedef struct
{
	unsigned int type;
	unsigned char text[1];
}message_t;

typedef struct
{
	unsigned int value;
	unsigned int queue[TASK_NUM_MAX];
}semaphore_t;

#endif
