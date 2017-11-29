/*
 * no_bloq_LCD.c
 *
 *  Created on: 28 de nov. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"



LCD_t my_LCD;

extern volatile int demoraLCD = 0;
uint8_t nb_LCDDelay(uint16_t demora)
{
	static uint8_t estado=0;
	if (!estado)
	{
	demoraLCD = demora;
	}
	estado=demoraLCD;
	return estado;
}

void nb_Display_lcd( char *msg , char r , char p )
{

	strcpy(my_LCD.msg,msg);
	my_LCD.r=r;
	my_LCD.p=p;
	my_LCD.busy=1;
}


void nb_driver_LCD (void)
{
	static uint8_t estado;
	static uint8_t i ;

	if (!(my_LCD.busy)) return;

	if (!estado)
	{
		if( my_LCD.r )
			my_LCD.p = my_LCD.p + 0xc0 ;
		else
			my_LCD.p = my_LCD.p + 0x80 ;

		estado++;
	}
	else if (estado==1)
	{
		if (!nb_WComando8(my_LCD.p))
		estado++;
		i=0;
	}
	else if (estado==3)
	{
		if (my_LCD.msg[ i ] != '\0')
		{
			if (!nb_WDato(my_LCD.msg[ i ]))
			i++;


		}
		else
		{	estado =0;
			my_LCD.busy=0;
		}
	}
}


uint8_t nb_WComando8(uint8_t comando){
	static uint8_t estado;
	if (!estado)
	{
	set_pin(LCD_RS,OFF);

	// Parte Alta del comando
	set_pin(LCD_D4,((comando & 0x10) >> 4));
	set_pin(LCD_D5,((comando & 0x20) >> 5));
	set_pin(LCD_D6,((comando & 0x40) >> 6));
	set_pin(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();

	if (!nb_LCDDelay(2))
		estado++;
	return 1;
	}
	else if (estado==1)
	{

	// Parte Baja del comando
	set_pin(LCD_D4,(comando & 0x01));
	set_pin(LCD_D5,((comando & 0x02) >> 1));
	set_pin(LCD_D6,((comando & 0x04) >> 2));
	set_pin(LCD_D7,((comando & 0x08) >> 3));
	LatchLcd();
	if (!nb_LCDDelay(4))
	{
		estado=0;
		return 0;
	}
	return 1;

	}

}

uint8_t nb_WDato (uint8_t dato)
{
	static uint8_t estado;

	if (!estado)
	{
	set_pin(LCD_RS,ON);
	// Parte Alta del comando
	set_pin(LCD_D4,((dato & 0x10) >> 4));
	set_pin(LCD_D5,((dato & 0x20) >> 5));
	set_pin(LCD_D6,((dato & 0x40) >> 6));
	set_pin(LCD_D7,((dato & 0x80) >> 7));
	LatchLcd();
	if (!nb_LCDDelay(2))
			estado++;
	return 1;
	}
	else
	{

	// Parte Baja del comando
	set_pin(LCD_D4,(dato & 0x01));
	set_pin(LCD_D5,((dato & 0x02) >> 1));
	set_pin(LCD_D6,((dato & 0x04) >> 2));
	set_pin(LCD_D7,((dato & 0x08) >> 3));
	LatchLcd();
	if (!nb_LCDDelay(2))
	{
		estado=0;
		return 0;
	}
	return 1;
	}
}
