#include <lib/types.h>
#include <ipc.h>
#include <lib/error.h>

int semaphore_init(semaphore_t *sem, int value)
{
	if((NULL == sem) || (value < 0))
	{
		return EPARAM;
	}
	
	sem->value = value;
	memset(sem->queue, 0, sizeof(sem->queue));
	return 0;
}

int semaphore_delete()
{
	return 0;
}

int semaphore_wait(semaphore_t *sem)
{
	sem->value--;
	if(sem->value <=0)
	{
		//
	}
	else
	{
	}
	
	return 0;
}

int semaphore_signal(semaphore_t *sem)
{
	sem->value++;
	if(sem->value > 0)
	{
	}
	else
	{
		
	}
	
	return 0;
}
