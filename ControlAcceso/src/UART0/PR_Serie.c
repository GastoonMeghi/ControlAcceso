/**
 	\file PR_serie.c
 	\brief Primitiva de comunicación serie
 	\details buffers de RX y TX protegidos
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include "PR_Serie.h"
#include "PR_Serie.h"
#include "FW_Serie.h"
#define START_TX_0()	((PopTx_0)((uint8_t*)&U0THR))
// Buffer de Transmision
uint8_t bufferTx_0[TXBUFFER_SIZE];
// Buffer de Recepcion
uint8_t bufferRx_0[RXBUFFER_SIZE];

// Indices de Transmision
uint8_t tx_in_0,tx_out_0;
// Indices de Recepcion
uint8_t rx_in_0,rx_out_0;
// Flags de estado de los buffers
uint8_t tx_buffer_full_0 = 0, tx_buffer_empty_0 = 1;
uint8_t rx_buffer_full_0 = 0, rx_buffer_empty_0 = 1;

uint8_t PushTx_0(uint8_t dato)
{
	if(tx_buffer_full_0)
		return 1;	//buffer lleno

	bufferTx_0[tx_in_0] = dato;
	tx_in_0++;
	tx_in_0 %= TXBUFFER_SIZE;
	tx_buffer_empty_0 = 0;	//si agrego un dato el buffer ya no esta vacio

	if(tx_in_0 == tx_out_0)
		tx_buffer_full_0 = 1;	//se lleno el buffer

	if (txStart_0 == 0)
	{
		txStart_0 = 1;
		START_TX_0();
	}
	return 0;	//dato agregado al buffer
}

uint8_t PopTx_0( uint8_t *dato )
{
	if(tx_buffer_empty_0)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferTx_0[tx_out_0];
	tx_out_0++;
	tx_out_0 %= TXBUFFER_SIZE;
	tx_buffer_full_0 = 0;	//si saco un dato el buffer ya no esta lleno

	if(tx_out_0 == tx_in_0)
		tx_buffer_empty_0 = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

uint8_t PushRx_0( uint8_t dato )
{
	if(rx_buffer_full_0)
		return 1;	//buffer lleno

	bufferRx_0[rx_in_0] = dato;
	rx_in_0 ++;
	rx_in_0 %= RXBUFFER_SIZE;
	rx_buffer_empty_0 = 0;	//si agrego un dato el buffer ya no esta vacio

	if(rx_in_0 == rx_out_0)
		rx_buffer_full_0 = 1;	//se lleno el buffer

	return 0;	//dato agregado al buffer
}

uint8_t PopRx_0( uint8_t *dato )
{
	if(rx_buffer_empty_0)
		return 1;	//buffer vacio

	*dato = (uint8_t) bufferRx_0[rx_out_0];
	rx_out_0++;
	rx_out_0 %= RXBUFFER_SIZE;
	rx_buffer_full_0 = 0;	//si saco un dato el buffer ya no esta lleno

	if(rx_out_0 == rx_in_0)
		rx_buffer_empty_0 = 1;	//se vacio el buffer

	return 0;	//dato sacado del buffer
}

void EnviarString_0 (const char *str)
{
	uint32_t i;
	for( i = 0 ; str[i] ; i++ )
		PushTx_0( str[i] );
}
