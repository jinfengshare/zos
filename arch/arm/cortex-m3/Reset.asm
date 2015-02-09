
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

Reset_Handler	PROC
	
	IMPORT main
	
	; prepare two mode stack
	LDR R0, =0X20020000
	MSR MSP, R0
	LDR R0, =0X20010000
	MSR PSP, R0

	LDR R0, =main
	BX R0
	
	ENDP
	
	ALIGN
	
	END