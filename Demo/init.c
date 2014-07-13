#include "task.h"

void main(void * arg);

int os_init(void)
{	
	task0_init();
	
	task_create(main);
	
	while(1)
	{
		__asm{SVC #0};
	}
}
