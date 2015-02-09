
	AREA	|.text|, CODE, READONLY
	
	EXPORT  __user_initial_stackheap	; need export!
		
__user_initial_stackheap
	;LDR     R0, =  Heap_Mem
	;LDR     R1, =(Stack_Mem + Stack_Size)
	;LDR     R2, = (Heap_Mem +  Heap_Size)
	;LDR     R3, = Stack_Mem
	BX      LR
	
	ALIGN
	
	END