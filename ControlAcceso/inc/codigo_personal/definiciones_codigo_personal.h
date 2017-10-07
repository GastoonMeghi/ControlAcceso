/*
 * definiciones_codigo_personal.h
 *
 *  Created on: 7 de oct. de 2017
 *      Author: Gaston
 */

#ifndef CODIGO_PERSONAL_DEFINICIONES_CODIGO_PERSONAL_H_
#define CODIGO_PERSONAL_DEFINICIONES_CODIGO_PERSONAL_H_

#define NORMAL 0
#define BUSY 1
#define READY 2
#define TIEMPO_VENCIDO 3
#define PRIMER_PEDIDO 4





#define ACTIVAR_TIMER_INGRESO_CODIGO T1TCR &= ~(0x01<<0);T1TCR|= (0x01<<1);	T1TCR &= ~(0x01<<1);T1TCR |= (0x01<<0); //activa el timer1
#define ENTER 7 //codigo entregado por la funcion Tecla cuando se presiona la tecla ENTER
#define MAX_DIGITOS 4


#endif /* CODIGO_PERSONAL_DEFINICIONES_CODIGO_PERSONAL_H_ */
