void task_uart(void * arg)
{
	while(1)
	{
		__asm{SVC #0};
	}
}