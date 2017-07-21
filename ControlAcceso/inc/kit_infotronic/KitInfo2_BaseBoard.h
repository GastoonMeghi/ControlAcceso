/*
 * KitInfo2_Baseboard.h
 *
 *  Created on: 17/04/2012
 *      Author: Mica y Chor
 */

#ifndef KIT_INFO2BASEBOARD_H_
#define KIT_INFO2BASEBOARD_H_

 	#include "aplicacion.h"
 
//Identificación de los puertos de expansion:
	#define EXPANSION0		PORT2,7
	#define EXPANSION1		PORT1,29
	#define EXPANSION2		PORT4,28
	#define EXPANSION3		PORT1,23
	#define EXPANSION4		PORT1,20
	#define EXPANSION5		PORT0,19
	#define EXPANSION6		PORT3,26
	#define EXPANSION7		PORT1,25
	#define EXPANSION8		PORT1,22
	#define EXPANSION9		PORT1,19
	#define EXPANSION10		PORT0,20
	#define EXPANSION11		PORT3,25
	#define EXPANSION12		PORT1,27
	#define EXPANSION13		PORT1,24
	#define EXPANSION14		PORT1,21
	#define EXPANSION15		PORT1,18
	#define EXPANSION16		PORT1,31
	#define EXPANSION17		PORT0,24
	#define EXPANSION18		PORT0,25
	#define EXPANSION19		PORT0,17
	#define EXPANSION20		PORT1,31
	#define EXPANSION21		PORT0,22
	#define EXPANSION22		PORT0,15
	#define EXPANSION23		PORT0,16
	#define EXPANSION24		PORT2,8
	#define EXPANSION25		PORT2,12
	#define EXPANSION26		PORT1,31
	#define EXPANSION27		PORT1,31

	//Leds (Reles)
	#define		LED1		PORT2,0 		//GPIO2
	#define		LED2		PORT0,23		//GPIO0
	#define		LED3		PORT0,21		//GPIO0
	#define		LED4		PORT0,27		//GPIO0

	//Led RGB:
	#define		RGBB		PORT2,1			//GPIO2
	#define		RGBR		PORT2,2			//GPIO2
	#define		RGBG		PORT2,3			//GPIO2
	#define		BUZZ		PORT0,28		//GPIO0

	//Teclas (teclado 4x1)
	#define		KEY0		PORT2,10		//SW1
	#define		KEY1		PORT0,18		//SW4
	#define		KEY2		PORT0,11		//SW7
	#define		KEY3_RC		PORT2,13		//SW10
	#define		KEY4_RC		PORT1,26		//SW13

	//Entradas digitales:
	#define		IN0		PORT4,29		//GPIO4
	#define		IN1		PORT2,11		//GPIO2
	#define		IN2		PORT1,26		//GPIO1

	//GPIOS LCD:
	#define		LCD_D4		PORT0,5			//GPIO0
	#define		LCD_D5		PORT0,10		//GPIO0
	#define		LCD_D6		PORT2,4			//GPIO2
	#define		LCD_D7		PORT2,5			//GPIO2

	#define		LCD_RS		PORT2,6			//GPIO2
	#define		LCD_BF		PORT0,28		//GPIO1
	#define		LCD_E		PORT0,4			//GPIO0

	//ADC
	#define 	ADC5		P1,31	//ADC5	//es el pote (OJO! el plano indica ADC0)
	#define 	ADC1		P0,24	//ADC1	//termistor
	#define 	ADC2		P0,25	//ADC2	//entrada libre


	//Defines generales:
	#define		OFF		0
	#define		ON		1

	#define		BUZZ_ON		0
	#define		BUZZ_OFF	1





#define LED_ROJO 0,22
#define LED_VERDE 3,25
#define LED_AZUL 3,26


////////////////////////////FUNCIONES////////////////

void inic_GPIO (void);


#endif /* KIT_INFO2_H_ */
