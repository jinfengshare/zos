
void shell(void)
{
	int fd = Open("uart1");
	
	Write(fd, "Hello", 5);
	
	while(1)
	{
		//Write(fd, "Hello", 5);
	}
}
