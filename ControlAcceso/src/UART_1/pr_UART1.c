#include "aplicacion.h"

// Buffer de Recepcion
uint8_t bufferRx[RXBUFFER_SIZE];

// Indices de Recepcion
uint8_t rx_in,rx_out;

// Flags de estado de los buffers
uint8_t rx_buffer_full = 0, rx_buffer_empty = 1;
//
uint8_t rx_buffer_state = 0;
//

// Buffer tarjeta
uint8_t bufferRFID[13];
uint8_t tarjeta = LEIDA;

uint8_t PushRx( uint8_t dato )
{
	if(rx_buffer_full)
		return 1;	//buffer lleno
	// nueva version
	if (rx_buffer_state == RXBUFFER_SIZE)
		return 1; // buffer lleno
	//
	bufferRx[rx_in] = dato;
	rx_in ++;
	rx_in %= RXBUFFER_SIZE;
	rx_buffer_empty = 0;	//si agrego un dato el buffer ya no esta vacio
	//
	rx_buffer_state++;
	//

	if(rx_in == rx_out)
		rx_buffer_full = 1;	//se lleno el buffer*/

	return 0;	//dato agregado al buffer
}

uint8_t PopRx( uint8_t *dato )
{
	if(rx_buffer_empty)
		return 1;	//buffer vacio
	// Nueva version
	if (!rx_buffer_state)
		return 1;	// Buffer vacio
	//
	*dato = (uint8_t) bufferRx[rx_out];
	rx_out++;
	rx_out %= RXBUFFER_SIZE;
	rx_buffer_full = 0;	//si saco un dato el buffer ya no esta lleno
	//
	rx_buffer_state--;
	//
	if(rx_out == rx_in)
		rx_buffer_empty = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

/*
 * void update_RFID()
 *
 * Descripcion:
 * 		(Esta funcion se debe llamarla en el systick)
 * 		Cuando la uart1 ya cargo mas de 20 datos en el bufferRx, comprueba si los datos del buffer
 * 		son los datos de una tarjeta o basura a traves de un byte de start '\002' y de stop '\003'.
 * 		Si los datos de la tarjeta son correctas, llena otro buffer que lo usa getRFID() para
 * 		obtener el codigo de la tarjeta (que lo activa y desactiva a traves de un flag).
 */

void update_RFID() {
	// Inicio:	valor int = 2, valor ascii = '\002'
	// Fin:		valor int = 3, valor ascii = '\003'
	static uint8_t i = 0;
	uint8_t dato;
	if( rx_buffer_state > 20 ) {
		if ( !(PopRx(&dato)) ) {
			if (dato == TARJETA_INGRESADA) {
				while (!PopRx(&dato) && i < 12) {
					bufferRFID[i] = dato;
					i++;
				}
				bufferRFID[i] = '\0';
			}
			if(dato == TARJETA_CORRECTA)
				tarjeta = SIN_LEER;
			else
				tarjeta = LEIDA;
			i = 0;
		}
	}
}

/*
 * int get_RFID(uint8_t *dato)
 *
 * Argumento:
 * 		dato es un array de 13 posiciones, en el que se carga el codigo de la tarjeta
 * 		13 posiciones: 12 datos de la tarjeta + 1 '\0'
 *
 * Salida:
 * 		si no hay tarjeta, ya se leyo o hubo error, devuelve 0
 * 		si leyo correctamente una tarjeta, devuelve 1
 *
 * Ejemplo de uso:
 *
 * 		uint8_t aux[13];
 * 		if(get_RFID(aux)) {
 *			// Si ingreso al if es porque se ingreso una nueva tarjeta (aux se cargo con el codigo)
 * 		}
 * 		else {
 *		// Si ingreso al else es porque no hay tarjeta, ya se leyo la tarjeta o el buffer tiene basura
 * 		}
 *
 */

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
