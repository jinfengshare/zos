#ifndef HLD_UART_H
#define HLD_UART_H

enum
{
	DMA_SEND = 1,
	DMA_RECV,
	DMA_RECV_SIZE,
	RECV_DATA_TIMESTAMP,
	POWER_SAVE,
};

void hal_uart1_init(void);
int hal_uart1_open(void);
int hal_uart1_close(void);
int hal_uart1_ctrl(int option, void *value, unsigned int optlen);
int hal_uart1_write(unsigned char *buffer, unsigned int len);
int hal_uart1_read(unsigned char *buffer, unsigned int len);

#endif
