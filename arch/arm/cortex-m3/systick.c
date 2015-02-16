#include "types.h"

static uint32_t systick_count = 0;

void systick_irq(void)
{
    systick_count++;

    // block event check
    check_delayed_task();

    do_schedule();
}

uint32_t systick_get(void)
{
    return systick_count;
}

