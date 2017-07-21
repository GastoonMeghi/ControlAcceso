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
	set_pinsel (KEY4_RC,0x03); //la selecciono como CAP0.0
	//set_pinmode (KEY4_RC,PULL_UP); //resistencia de pull up interna
	T0PR = 30000; //CAMBIAR ESTE VALOR
	T0CTCR &= ~(0x03<<0); //TIMER

	T0CCR |= (0x01<<1)| (0x01<<2); //cap0.0 FE y genera interrupcion

	T0TCR &= ~(0x01<<0);
	T0TCR|= (0x01<<1);
	T0TCR &= ~(0x01<<1);
	T0TCR |= (0x01<<0);

	ISER0 |= (0x01<<1);


}





