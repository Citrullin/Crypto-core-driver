#ifndef CRYPTO_CORE_DRIVER_UART_H
#define CRYPTO_CORE_DRIVER_UART_H

#include <jansson.h>

int uart_set_interface_attribs(int fd, int speed, int parity);
int uart_open(void);
char * uart_read(void);
void uart_write(json_t * json_ptr);
int uart_init(void);

#endif //CRYPTO_CORE_DRIVER_UART_H
