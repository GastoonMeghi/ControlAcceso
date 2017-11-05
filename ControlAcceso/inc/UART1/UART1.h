#ifndef UART_1_H_
#define UART_1_H_

#include "aplicacion.h"

#define RXBUFFER_SIZE		40
#define LEIDA				1
#define SIN_LEER			0
#define TARJETA_INGRESADA	2
#define TARJETA_CORRECTA	3

void	Inic_UART1	();
uint8_t	PushRx 		(uint8_t dato);
uint8_t	PopRx		(uint8_t *dato);
void	update_RFID	();
uint8_t	get_RFID	(uint8_t *dato);

#endif /* UART_1_H_ */
