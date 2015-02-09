#include "types.h"

static uint32_t systick_count = 0;

void systick_init(void)
{
    systick_count = 0;
}

void systick_irq(void)
{
    systick_count++;

    check_delayed_task();
}

uint32_t systick_get(void)
{
    return systick_count;
}

