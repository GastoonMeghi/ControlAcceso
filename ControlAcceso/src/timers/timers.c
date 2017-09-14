/*
 * timers.c
 *
 *  Created on: 4 de jun. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"

void inic_timer0 (void)
{

	PCONP|= (0x01<<0);
	PCLKSEL0 &= ~(0x03<<PCLK_TIMER0); //lo ajusto en CCLK/4
	T0PR = 0; //cada pulso de clock son 0,01 useg
	T0CTCR &= ~(0x03<<0); //TIMER
	T0MCR |= (0x01)|(0x01<<1); //el match interrumpe y resetea
	T0MR0 = 4444; // el mach se produce cada 44,44 useg 22500hz
	T0TCR &= ~(0x01<<0);
	T0TCR|= (0x01<<1);
	T0TCR &= ~(0x01<<1);
	T0TCR |= (0x01<<0);

	ISER0 |= (0x01<<1);


}





