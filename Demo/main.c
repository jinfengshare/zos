/* 
 * Create: jinfeng, 2014/7/28
 * 
 * kernel entry, do device init, file system init, create task 0, and change to user mode
 * after these been done, we move to the first user task, which support an terminal process!
 *
 */

int hardware_init(void)
{
	// file system init
	//dm_init();

	// device init
	hal_uart1_init();
}

