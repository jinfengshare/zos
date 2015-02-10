void taskA(void * arg)
{
	while(1)
	{
        sleep(2000);
	}
}

void taskB(void * arg)
{
	while(1)
	{
        sleep(10000);
	}
}

void user_task(void *arg)
{
    task_create(taskA);
    task_create(taskB);
    
    while(1)
    {
        sleep(3000);
    }
}

