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


void inic_timer1 (void)
{

	PCONP|= (0x01<<2);
	PCLKSEL0 &= ~(0x00<<4); //lo ajusto en CCLK/8
	PCLKSEL0 |= (0x01<<4); //lo ajusto en CCLK/8
	T1PR = 6250000; //cada pulso de clock son 1seg
	T1CTCR &= ~(0x03<<0); //TIMER
	T1MCR |= (0x01)|(0x01<<1)|(0x01<<2); //el match interrumpe, stop y resetea
	T1MR0 = 1; // el mach se produce cada 1seg
	T1TCR &= ~(0x01<<0);
	T1TCR|= (0x01<<1);
	T1TCR &= ~(0x01<<1);
	ISER0 |= (0x01<<2);
	//NO LO ACTIVO, SE ACTIVA DESDE void capturar_y_mostrar_codigo (void)

}



