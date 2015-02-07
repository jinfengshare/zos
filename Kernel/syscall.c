#include "types.h"

#include "syscall.h"

/*-------------+--------------------+-------------
 *
 */
__asm
void svc_trigger(int number, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    PUSH {R0-R4}
    SVC #0
    POP {R0-R4}
}

__asm
void get_svc_number(int *number, uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d)
{
    MRS R5, PSP

    // SVC number
    LDR R6, [R5]
    STR R6, [R0]

    // a
    LDR R6, [R5, 4]
    STR R6, [R1]

    // b
    LDR R6, [R5, 8]
    STR R6, [R2]

    // c
    LDR R6, [R5, 12]
    STR R6, [R3]

    // d
    LDR R6, [R5, 16]
    STR R6, [R4]

    BX LR
}

/*-------------+--------------------+-------------
 *
 */

__asm
void do_schedule(void)
{
    PRESERVE8 {TRUE}

    IMPORT os_task_switch
    IMPORT g_cur_task
	
	; protext LR
	PUSH {LR}

    MRS R0, PSP
    STMDB R0!, {R4-R11}
    LDR R3, =g_cur_task
    STR R0, [R3, #0]

	BL os_task_switch

    //move PSP to the new task stack top
	LDR R0, =g_cur_task
	LDR R1, [R0]
	//fixed bug: unstacked R4-R11, which has been 'pushed' by user
	LDMIA.W R1!, {R4-R11}
	MSR PSP, R1

	POP {LR}
	BX LR
}

__asm
void do_sleep(int ms)
{
    PRESERVE8 {TRUE}

    IMPORT move_curtask_to_delay
    IMPORT os_curtask_save
    IMPORT os_switch2next_task
    IMPORT g_cur_task

    // must be first as pop at end: protext LR
	PUSH {LR}

    // protect param: ms
    PUSH {R0}

    // store all context
    MRS R0, PSP
    STMDB R0!, {R4-R11}
    LDR R3, =g_cur_task
    STR R0, [R3, #0]

    BL os_curtask_save
    
    POP {R0}
    BL move_curtask_to_delay
    
    BL os_switch2next_task

    //move PSP to the new task stack top
	LDR R0, =g_cur_task
	LDR R1, [R0]
	//fixed bug: unstacked R4-R11, which has been 'pushed' by user
	LDMIA.W R1!, {R4-R11}
	MSR PSP, R1

    POP {LR}
	BX LR
}


void do_default(int a, int b, int c, int d)
{
    // none
}

/*-------------+--------------------+-------------
 *
 */

void svc_handler(void)
{
    int number;

    uint32_t a,b,c,d;
    
    get_svc_number(&number, &a, &b, &c, &d);

    switch(number)
    {
        case SVC_SLEEP:
            do_sleep(a);
            break;
        case SVC_SCHEDULE:
            do_schedule();
            break;
        default:
            do_default(a, b, c, d);
            break;
    }
}

