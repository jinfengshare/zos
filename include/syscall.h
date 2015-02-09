#ifndef SYSCALL_H
#define SYSCALL_H

typedef void (*svc_func_t)(int a, int b, int c, int d);

enum
{
    SVC_SLEEP = 0,
    SVC_SCHEDULE,
};

#endif
