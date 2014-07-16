
; jinfeng, 2014/6/11
		
	;INCLUDE syscall.asm
		
	PRESERVE8 {TRUE}
		
	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

SVC_Handler	PROC
	
	; get interrupt number
	MRS R0, PSP
	LDR R1, [R0, #24]
	LDRB R0, [R1, #-2]
	
	;  as we will use BL later
	PUSH {LR}
	
	CMP R0, #3
	BNE syscall_end
	BL schedule
	
syscall_end
	POP {LR}
	BX LR
	
	ENDP

schedule	PROC
	IMPORT g_cur_task
	IMPORT os_task_switch
	
	; protext LR
	PUSH {LR}
	
	;Push the rest registers into task's stack
	MRS R0, PSP
	STMDB R0!, {R4-R11}
	;Update stack top to TCB
	LDR R3, =g_cur_task
	STR R0, [R3, #0]

	BL os_task_switch

	; move PSP to the new task stack top
	LDR R0, =g_cur_task
	LDR R1, [R0]
	; fixed bug: unstacked R4-R11, which has been 'pushed' by user
	LDMIA.W R1!, {R4-R11}
	MSR PSP, R1
	
	POP {LR}
	BX LR
	
	ENDP
		
	ALIGN
		
	END