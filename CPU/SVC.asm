
; jinfeng, 2014/6/11
		
	;INCLUDE syscall.asm
		
	PRESERVE8 {TRUE}
		
	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

SVC_Handler	PROC
	IMPORT svc_handler

	PUSH {LR}
	
	BL svc_handler
	
	POP {LR}
	
	BX LR
	
	ENDP
		
	ALIGN

	END