
__asm
void enter_user_mode(void)
{
    // change to user mode
	MRS R0, CONTROL
	ORR R0, #3
	MSR CONTROL, R0

    BX LR
}

extern void user_task(void *arg);

int kernel_init(void)
{
    // create first task
	task0_init();
}

void kernel_entry(void)
{
    kernel_init();

    enter_user_mode();

    task_create(user_task);

    while(1)
    {
        sleep();
    }
}

