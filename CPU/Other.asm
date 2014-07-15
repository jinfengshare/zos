
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

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