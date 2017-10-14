
/*
 * lcd.c
 *
 *  Created on: 24/09/2013
 *      Author: gabriel
 *
 * Driver de display:
 * Tiene un problema de tiempos ya que no se ejecuta bién sin el debugger.
 * Adecuar las rutinas de la cátedra a mis inicializaciones
 *
 */
#include "aplicacion.h"

volatile int demoraLCD;
uint8_t bufferLCD[100];
uint8_t entero_ascii[6];

/**
 * void LCDWaitLong(uint8_t ciclos)
 * Demora larga por SW
 *
 * */
void LCDWaitLong(uint16_t ciclos)
{
	uint16_t i;
	uint16_t x;

	for(i=0;i<ciclos;i++)
	{
		for(x = 0;x < 0x4FF6;x++);
	}
}

/**
 * void LCDWaitShort(uint8_t ciclos)
 * Demora corta por SW
 *
 * */
void LCDWaitShort(uint8_t ciclos)
{
	uint8_t i;
	uint16_t x;

	for(i=0;i<ciclos;i++)
	{
		for(x=0;x<0x9F6;x++);
	}
}


/**
 * void LCDDelay(uint16_t demora)
 * Demora medida por el tick
 *
 * */

void LCDDelay(uint16_t demora){

	demoraLCD = demora;
	while(demoraLCD);

}


/**
 * void LatchLcd(void)
 * Genera pulso de latch para LCD
 *
 * */
void LatchLcd(void){
	uint16_t i;

	set_pin(LCD_E,ON);
	//LCDDelay(2);
	LCDWaitLong(15);
	for(i = 0; i < 120; i++);
	set_pin(LCD_E,OFF);
}

/**
 * void Conversor(uint16_t valor_int)
 * Convierte un entero sin signo en ascii
 *
 * */
void Conversor(uint16_t valor_int){
	entero_ascii[4] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[3] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[2] = valor_int % 10 +48;
	valor_int /= 10;

	entero_ascii[1] = valor_int % 10 +48;
	entero_ascii[0] = valor_int /10 +48;

}

/**
 * void DisplayInt_lcd(uint16_t valor , uint8_t r , uint8_t p )
 * Escribe un entero en el LCD en la línea indicada por r
 * A partir de la posicion indicada por p
 *
 * */
void DisplayInt_lcd(uint16_t valor , uint8_t r , uint8_t p ){
	uint8_t i ;
	uint8_t flag_cero = 0;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	WComando8(p);
	Conversor(valor);
	for( i = 0 ; i < 5; i++ ){
		if(flag_cero == 0){
			if(entero_ascii[ i ] != '0'){
				flag_cero = 1;
				WDato(entero_ascii[ i ]);
			}
		}else{
			WDato(entero_ascii[ i ]);
		}

	}
}



/**
 * void Display_lcd( char *msg , char r , char p )
 * Escribe una cadena en el LCD en la línea indicada por r
 * A partir de la posicion indicada por p
 *
 * */
void Display_lcd( char *msg , char r , char p ){
	unsigned char i ;

	if( r )
        p = p + 0xc0 ;
	else
		p = p + 0x80 ;

	WComando8(p);
	for( i = 0 ; msg[ i ] != '\0' ; i++ )
		WDato(msg[ i ]);

}



/**
 * void Inic_PinesLCD(void)
 * Configura pines para manejo de LCD interfaz de 4 bits
 *
 * */
void Inic_PinesLCD(void){
	set_pinsel(LCD_RS,PINSEL_GPIO);
	set_dir(LCD_RS,SALIDA);
	set_pinmodeOD(LCD_RS,OPEN_DRAIN);
	set_pin(LCD_RS,OFF);

	set_pinsel(LCD_E,PINSEL_GPIO);
	set_dir(LCD_E,SALIDA);
	set_pinmodeOD(LCD_E,OPEN_DRAIN);
	set_pin(LCD_E,OFF);

	set_pinsel(LCD_D4,PINSEL_GPIO);
	set_dir(LCD_D4,SALIDA);
	set_pinmodeOD(LCD_D4,OPEN_DRAIN);
	set_pin(LCD_D4,OFF);

	set_pinsel(LCD_D5,PINSEL_GPIO);
	set_dir(LCD_D5,SALIDA);
	set_pinmodeOD(LCD_D5,OPEN_DRAIN);
	set_pin(LCD_D5,OFF);

	set_pinsel(LCD_D6,PINSEL_GPIO);
	set_dir(LCD_D6,SALIDA);
	set_pinmodeOD(LCD_D6,OPEN_DRAIN);
	set_pin(LCD_D6,OFF);

	set_pinsel(LCD_D7,PINSEL_GPIO);
	set_dir(LCD_D7,SALIDA);
	set_pinmodeOD(LCD_D7,OPEN_DRAIN);
	set_pin(LCD_D7,OFF);
}

/**
 * void WComando8(uint8_t comando)
 * Escribe un comando al LCD luego de inicialización
 * No usa BF
 *
 * */
void WComando8(uint8_t comando){
	set_pin(LCD_RS,OFF);

	// Parte Alta del comando
	set_pin(LCD_D4,((comando & 0x10) >> 4));
	set_pin(LCD_D5,((comando & 0x20) >> 5));
	set_pin(LCD_D6,((comando & 0x40) >> 6));
	set_pin(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	// Parte Baja del comando
	set_pin(LCD_D4,(comando & 0x01));
	set_pin(LCD_D5,((comando & 0x02) >> 1));
	set_pin(LCD_D6,((comando & 0x04) >> 2));
	set_pin(LCD_D7,((comando & 0x08) >> 3));
	LatchLcd();
	LCDDelay(4);

}

/**
 * void WComando4(uint8_t comando)
 * Escribe un comando al LCD en el proceso de inicialización
 * No usa BF
 *
 * */
void WComando4(uint8_t comando){
	set_pin(LCD_RS,OFF);
	set_pin(LCD_D4,((comando & 0x10) >> 4));
	set_pin(LCD_D5,((comando & 0x20) >> 5));
	set_pin(LCD_D6,((comando & 0x40) >> 6));
	set_pin(LCD_D7,((comando & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

}

/**
 * void WDato (uint8_t dato)
 * Escribe un dato al LCD en interfaz de 4 bits
 * No usa BF
 *
 * */
void WDato (uint8_t dato)
{
	set_pin(LCD_RS,ON);
	// Parte Alta del comando
	set_pin(LCD_D4,((dato & 0x10) >> 4));
	set_pin(LCD_D5,((dato & 0x20) >> 5));
	set_pin(LCD_D6,((dato & 0x40) >> 6));
	set_pin(LCD_D7,((dato & 0x80) >> 7));
	LatchLcd();
	LCDDelay(2);

	// Parte Baja del comando
	set_pin(LCD_D4,(dato & 0x01));
	set_pin(LCD_D5,((dato & 0x02) >> 1));
	set_pin(LCD_D6,((dato & 0x04) >> 2));
	set_pin(LCD_D7,((dato & 0x08) >> 3));
	LatchLcd();
	LCDDelay(2);

}

/**
 * void WString (uint8_t *ptr)
 * Escribe cadena de caracteres al LCD
 * No posiciona
 *
 * */
void WString (uint8_t *ptr)
{
	while(*ptr != 0x00)
	{
		WDato(*ptr++);
	}
}



/**
 * void Inic_LCD(void)
 * Inicializa LCD en modo de 4 bits de datos
 * No usa BF
 *
 * */
void Inic_LCD(void)
{
	Inic_PinesLCD();		// Configura pines de interfaz con LCD
	LCDDelay(400);			// Demora inicial

	LCDWaitLong(15);		// Funsion Set para 4 bits
	WComando4(MODO_8BITS);
	LCDWaitLong(15);
	WComando4(MODO_8BITS);
	LCDWaitShort(6);
	WComando4(MODO_8BITS);
	LCDWaitShort(6);
	WComando4(MODO_4BITS);		// 4 bits
	LCDWaitShort(3);
	WComando4(MODO_4BITS);		// 4 bits
	LCDWaitShort(3);
	WComando4(LIMPIA_LCD);		// Clear del LCD
	LCDWaitShort(12);
	WComando4(APAGA_LCD_CURSOR);		// Display y cursor off
	LCDWaitShort(3);
	WComando4(LINEAS_FROMATO);		// Display de dos lineas caractetes de 5x11
	LCDWaitShort(15);
	WComando8(LCD_CLEAR);	// Limpia LCd y va a Home

}

