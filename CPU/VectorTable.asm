	
; jinfeng, 2014/6/11

	INCLUDE Reset.asm
	INCLUDE PendSV.asm
	INCLUDE SysTick.asm
	INCLUDE SVC.asm
	INCLUDE Other.asm
	
	AREA	RESET, DATA, READONLY
;-------------------------------------------------------------------------------

	; internal interrupt
	DCD		0x20002000
	DCD		Reset_Handler
	DCD		NMI_Handler
	DCD		HardFault_Handler
	DCD		MemManage_Handler
	DCD		BusFault_Handler
	DCD		UsageFault_Handler
	DCD		0
	DCD		0
	DCD		0
	DCD		0
	DCD		SVC_Handler
	DCD		DebugMon_Handler
	DCD		0
	DCD		PendSV_Handler
	DCD		SysTick_Handler

	END