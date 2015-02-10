
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Reset_Handler	PROC
	
	IMPORT __main
	
	; prepare two mode stack
	LDR R0, =0X20020000
	MSR MSP, R0
	LDR R0, =0X20010000
	MSR PSP, R0

	LDR R0, =__main
	BX R0
	
	ENDP

SVC_Handler	PROC
	PRESERVE8 {TRUE}
	IMPORT svc_handler

	PUSH {LR}
	
	BL svc_handler
	
	POP {LR}
	
	BX LR
	
	ENDP

PendSV_Handler	PROC
    	EXPORT  PendSV_Handler         [WEAK]
	B .
	ENDP
	
SysTick_Handler	PROC
    	EXPORT  SysTick_Handler         [WEAK]
	B	.
	ENDP
	
NMI_Handler	PROC
    
	BX LR
	ENDP

HardFault_Handler	PROC

	B	.
	ENDP
	
MemManage_Handler	PROC

	B	.
	ENDP
	
BusFault_Handler	PROC

	B	.
	ENDP

UsageFault_Handler	PROC

	B	.
	ENDP
	
DebugMon_Handler	PROC

	B	.
	ENDP
	
	END