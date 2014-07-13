#include "task.h"

void main(void * arg)
{
	while(1)
	{
		__asm{SVC #0};
	}
}