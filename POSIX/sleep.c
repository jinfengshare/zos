#include "syscall.h"

void sleep(int ms)
{
    if(0 == ms)
    {
        svc_trigger(SVC_SCHEDULE, 0, 0, 0, 0);
    }
    else
    {
        svc_trigger(SVC_SLEEP, ms, 0, 0, 0);
    }
}
