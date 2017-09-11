/*
 * dac.c
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"

void inic_dac (void)
{
	set_pinsel (P026,AOUT); //conecto el DAC
	set_pinmodeOD (P026,0); //0:modo normal 1:open drain
}



void escribir_dac (int dato)
{
	dato&=0x3FF; // 1111111111 evito que el dato sea mayor a 10 bits
	DACR|= dato;
}
