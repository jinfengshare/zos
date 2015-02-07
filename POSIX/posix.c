
#include "syscall.h"

void schedule(void)
{
    svc_trigger(SVC_SCHEDULE, 0, 0, 0, 0);
}

