#include "task.h"

int os_init(void)
{	
	board_init();
	
	task0_init();
	
	task_create(main);

	while(1)
	{
		sleep();
	}
}
