#include <platform/platform.h>
#include <fs/file.h>

void dm_uart_init(void)
{
	file_t uartfile;
	
	memset(&uartfile, 0, sizeof(uartfile));
	strcpy(uartfile.filename, "uart1");
	uartfile.open = hal_uart1_open;
	uartfile.close = hal_uart1_close;
	uartfile.read = hal_uart1_read;
	uartfile.write = hal_uart1_write;
	uartfile.ioctrl = hal_uart1_ctrl;

	Create(&uartfile);
}

// driver manager
void dm_init(void)
{
	fs_init();
	dm_uart_init();
}

