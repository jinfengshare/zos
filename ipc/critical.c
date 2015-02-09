void ENTER_CRITICAL(void)
{
    __asm{ CPSID I; }
}

void EXIT_CRITICAL(void)
{
    __asm{ CPSIE I; }
}

