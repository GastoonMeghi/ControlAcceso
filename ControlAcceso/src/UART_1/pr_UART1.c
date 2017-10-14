#include "aplicacion.h"

// Buffer de Recepcion
uint8_t bufferRx[RXBUFFER_SIZE];

// Indices de Recepcion
uint8_t rx_in,rx_out;

// Flags de estado de los buffers
uint8_t rx_buffer_full = 0, rx_buffer_empty = 1;

// Buffer tarjeta
uint8_t bufferRFID[13];
uint8_t tarjeta = LEIDA;

uint8_t PushRx( uint8_t dato )
{
	if(rx_buffer_full)
		return 1;	//buffer lleno

	bufferRx[rx_in] = dato;
	rx_in ++;
	rx_in %= RXBUFFER_SIZE;
	rx_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio

	if(rx_in == rx_out)
		rx_buffer_full = 1;	//se lleno el buffer

	return 0;	//dato agregado al buffer
}

uint8_t PopRx( uint8_t *dato )
{
	if(rx_buffer_empty)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferRx[rx_out];
	rx_out++;
	rx_out %= RXBUFFER_SIZE;
	rx_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno

	if(rx_out == rx_in)
		rx_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

void update_RFID() {
	// Inicio:	valor int = 2, valor ascii = '\002'
	// Fin:		valor int = 3, valor ascii = '\003'
	static uint8_t i = 0;
	uint8_t dato;
	if( !(PopRx(&dato)) ) {
		if (dato == TARJETA_INGRESADA) {
			while (!PopRx(&dato) && i < 12) {
				bufferRFID[i] = dato;
				i++;
			}
			bufferRFID[i] = '\0';
		}
		tarjeta = SIN_LEER;
		i = 0;
	}
}

int get_RFID(uint8_t *dato) {
	if (tarjeta == LEIDA) {
		return 0;
	}
	uint8_t i = 0;
	while (i < 13) {
		dato[i] = bufferRFID[i];
		i++;
	}
	tarjeta = LEIDA;
	return 1;
}
