void taskA(void * arg)
{
	while(1)
	{
        printf("taskA\r\n");
        
        sleep(2000);
	}
}

void taskB(void * arg)
{
	while(1)
	{
        printf("taskB\r\n");
        
        sleep(10000);
	}
}

void user_task(void *arg)
{
    debug_init();

    task_create(taskA);
    task_create(taskB);
    
    while(1)
    {
        printf("user_task\r\n");
        
        sleep(3000);
    }
}

