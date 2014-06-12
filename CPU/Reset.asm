
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Reset_Handler	PROC

	IMPORT init
		
	; prepare data
	LDR R0, =0X20020000
	MSR MSP, R0
	LDR R0, =0X20010000
	MSR PSP, R0
	
	MRS R0, CONTROL
	ORR R0, #3
	MSR CONTROL, R0
	
	LDR R0, =init
	BX R0
	
	ENDP
	
	ALIGN
	
	END