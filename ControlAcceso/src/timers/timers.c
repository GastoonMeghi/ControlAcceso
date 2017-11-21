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
	T0PR = 0;
	T0MR0 =1110; //ajustado para 44,44useg//20,83uS
	T0CTCR &= ~(0x03<<0); //TIMER
	T0MCR |= (0x01<<0)|(0x01<<1); //el match 0 del timer 0 interrumpe y resetea el contador

	T0TCR &= ~(0x01<<0);
	T0TCR|= (0x01<<1);
	T0TCR &= ~(0x01<<1);
	T0TCR |= (0x01<<0);

	ISER0 |= (0x01<<1);
}


//void inic_timer1 (void)
//{
//
//	PCONP|= (0x01<<2);
//	PCLKSEL0 |= ~(0x03<<4); //lo ajusto en CCLK/8
//	T1PR = 12499999; //cada pulso de clock son 1seg
//	T1CTCR &= ~(0x03<<0); //TIMER
//	T1MCR |= (0x01)|(0x01<<1)|(0x01<<2); //el match interrumpe, stop y resetea
//	T1MR0 = 20; // el match se produce cada 20seg
//	T1TCR &= ~(0x01<<0);
//	T1TCR|= (0x01<<1);
//	ISER0 |= (0x01<<2);
//	//NO LO ACTIVO, SE ACTIVA DESDE void capturar_y_mostrar_codigo (void)
//
//}



