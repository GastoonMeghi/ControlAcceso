/*
 * nb_LCD.h
 *
 *  Created on: 29 de nov. de 2017
 *      Author: Gaston
 */

#ifndef LCD_NB_LCD_H_
#define LCD_NB_LCD_H_

typedef struct
{
	char msg[16];
	char r;
	char p;
	char busy;
}LCD_t;

uint8_t nb_LCDDelay(uint16_t demora);

void nb_Display_lcd( char *msg , char r , char p );


void nb_driver_LCD (void);


uint8_t nb_WComando8(uint8_t comando);

uint8_t nb_WDato (uint8_t dato);

#endif /* LCD_NB_LCD_H_ */
