#include <ipc.h>
#include <task.h>
#include <types.h>

int send_message(int tid, message_t *msg)
{
	os_tcb_t *tcb;
	
	// check param
	if((tid < 0) || (tid >= TASK_NUM_MAX) || (NULL == msg))
	{
		return -1;
	}
	
	// check invalidation
	tcb = get_tcb(tid);
	if((tcb->id <= 0)||(NULL == tcb))
	{
		return -1;
	}
	
	
	return 0;
}

int recv_message(int tid, message_t *msg)
{
	// check param
	if((tid < 0) || (tid >= TASK_NUM_MAX) || (NULL == msg))
	{
		return -1;
	}
	
	return 0;
}

