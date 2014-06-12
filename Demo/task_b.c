#include "task.h"

void task_b(void *arg)
{
	while(1)
	{
		__asm{SVC #0};
	}
}