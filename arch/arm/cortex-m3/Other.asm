
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Reset_Handler	PROC
	
	IMPORT __main
  
	LDR R0, =0X20020000
	MSR MSP, R0
	LDR R0, =0X20010000
	MSR PSP, R0

	LDR R0, =__main
	BX R0
	
	ENDP

SVC_Handler	PROC
	EXPORT  SVC_Handler         [WEAK]
	B .
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
	EXPORT  NMI_Handler         [WEAK]
	B .
	ENDP
	ENDP

HardFault_Handler	PROC
	IMPORT hard_fault_handler_c
	
	TST LR, #4
	ITE EQ
	MRSEQ R0, MSP
	MRSNE R0, PSP
	B hard_fault_handler_c
	ENDP
	
	END
	