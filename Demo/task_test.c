
void taskA(void * arg)
{
	while(1)
	{
		sleep();
	}
}

void taskB(void * arg)
{
	while(1)
	{
		sleep();
	}
}

void user_task(void *arg)
{
    task_create(taskA);
    task_create(taskB);
    
    while(1)
    {
        sleep();
    }
}

