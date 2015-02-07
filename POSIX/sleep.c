#include "syscall.h"

void sleep(int ms)
{
    svc_trigger(SVC_SLEEP, ms, 0, 0, 0);
}

