
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Reset_Handler	PROC
	
	IMPORT shell
	IMPORT kernel_entry
	
	; prepare two mode stack
	LDR R0, =0X20020000
	MSR MSP, R0
	LDR R0, =0X20010000
	MSR PSP, R0

	LDR R0, =kernel_entry
	BX R0
	
	ENDP
	
	ALIGN
	
	END