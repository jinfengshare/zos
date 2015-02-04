#include <ipc.h>
#include <task.h>
#include <lib/types.h>
#include <lib/error.h>

int send_message(int tid, message_t *msg)
{
	os_tcb_t *tcb;
	
	// check param
	if((tid < 0) || (tid >= TASK_NUM_MAX) || (NULL == msg))
	{
		return EPARAM;
	}
	
	// check invalidation
	tcb = get_tcb(tid);
	if((tcb->id <= 0)||(NULL == tcb))
	{
		return EPARAM;
	}
	
	
	return 0;
}

int recv_message(int tid, message_t *msg)
{
	// check param
	if((tid < 0) || (tid >= TASK_NUM_MAX) || (NULL == msg))
	{
		return EPARAM;
	}
	
	return 0;
}

