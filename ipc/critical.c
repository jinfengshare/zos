
static int critical_count = 0;

void ENTER_CRITICAL(void)
{
    __asm{ CPSID I; }

    critical_count++;
}

void EXIT_CRITICAL(void)
{
    critical_count--;
    
    if(0 == critical_count)
    {
        __asm{ CPSIE I; }
    }
}

