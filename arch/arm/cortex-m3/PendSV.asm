
; jinfeng, 2014/6/11

	AREA	|.text|, CODE, READONLY
;-------------------------------------------------------------------------------

PendSV_Handler	PROC
    EXPORT  PendSV_Handler         [WEAK]
	B .
	ENDP
	
	END