void taskA(void * arg)
{
	while(1)
	{
        PowerLED_Off();
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
    PowerLED_Init();

    task_create(taskA);
    task_create(taskB);
    
    while(1)
    {
        PowerLED_On();
        sleep(3000);
    }
}

