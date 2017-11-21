/*
 * PR_Serie.h
 *
 *  Created on: 09/07/2013
 *
 */

#ifndef PR_SERIE_H_
#define PR_SERIE_H_

#include "FW_Serie.h"
#include "RegsLPC1769.h"

#define TXBUFFER_SIZE	32
#define RXBUFFER_SIZE	32

uint8_t PushTx_0(uint8_t dato);
uint8_t PopTx_0( uint8_t *dato );
uint8_t PushRx_0(uint8_t dato);
uint8_t PopRx_0( uint8_t *dato );
void EnviarString_0 (const char *str);

#endif /* PR_SERIE_H_ */
