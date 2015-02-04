#include <spinlock.h>

__asm void spin_lock(spinlock_t *lock)
{
	MOV R2, #1
try
	LDRBEX R1, [R0]
	CMP R1, #0
	BNE try
	STRBEX R1, R2, [R0]
	CMP R1, #0
	BNE try
	BX LR
}

__asm void spin_unlock(spinlock_t *lock)
{
	/*
	MOV R1, #0
	LDR R2, =lock
try
	LDRBEX R0, [lock]
	CMP R0, #1
	STRBEXEQ R0, R1, [lock]
	CMP R0, #0
	BNE try
	BX LR
	*/
}
