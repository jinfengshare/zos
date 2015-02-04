#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <task.h>

typedef struct
{
	unsigned char lock;
	unsigned char queue[TASK_NUM_MAX];
}spinlock_t;

void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);

#endif