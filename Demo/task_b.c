#include "task.h"

int task_b(void *arg)
{
	while(1)
	{
		__asm{SVC #0};
	}
}