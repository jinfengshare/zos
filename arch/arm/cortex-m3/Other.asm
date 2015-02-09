
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

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