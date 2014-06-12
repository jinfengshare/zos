
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

SVC_Handler	PROC
	
	IMPORT g_tcb_a
	IMPORT g_tcb_b
	IMPORT g_cur_task
	
	; Store Regs last
	MRS R0, PSP
	STMDB R0!, {R4-R11}
	
	LDR R3, =g_cur_task
	STR R0, [R3, #0]	; update stack top
	
	PUSH {LR}
	
task_switch
	; select one task
	LDR R0, =g_cur_task
	LDR R1, [R0, #8]
	CMP R1, #2
	BEQ update_task_b_tcb
	
update_task_a_tcb
	LDR R0, =g_cur_task
	LDR R1, =g_tcb_a
	LDMIA.W R0!, {R2, R3, R4}
	STMIA.W R1!, {R2, R3, R4}
	B switch_task_b
	
update_task_b_tcb
	LDR R0, =g_cur_task
	LDR R1, =g_tcb_b
	LDMIA.W R0!, {R2, R3, R4}
	STMIA.W R1!, {R2, R3, R4}
	B switch_task_a

	; copy the task context to current
switch_task_a
	LDR R0, =g_cur_task
	LDR R1, =g_tcb_a
	LDMIA.W R1!, {R2, R3, R4}
	STMIA.W R0!, {R2, R3, R4}
	B switch_end
	
switch_task_b
	LDR R0, =g_cur_task
	LDR R1, =g_tcb_b
	LDMIA.W R1!, {R2, R3, R4}
	STMIA.W R0!, {R2, R3, R4}
	
switch_end
	; move PSP to the new task stack top
	LDR R0, =g_cur_task
	LDR R1, [R0]
	
	; fixed bug: stacked full regs
	LDMIA.W R1!, {R4-R11}
	
	MSR PSP, R1

do_switch
	POP {LR}
	
	BX LR
	
	ENDP
	
	ALIGN
		
	END