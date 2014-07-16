void sleep(int ms)
{
	__asm{SVC #3}
}