/*
 * teclado_exp3.c
 *
 *  Created on: 5 de jun. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"

 __RW uint8_t buff_key=NO_KEY;

uint8_t teclado_hw (void)
{

		EX3_columna0_OFF;
		EX3_columna1_ON;

		if (!EX3_fila0)
		return 0;
		else if (!EX3_fila1)
		return 1;
		else if (!EX3_fila2)
		return 2;
		else if (!EX3_fila3)
		return 3;

		EX3_columna0_ON;
		EX3_columna1_OFF;

		if (!EX3_fila0)
		return 4;
		else if (!EX3_fila1)
		return 5;
		else if (!EX3_fila2)
		return 6;
		else if (!EX3_fila3)
		return 7;
		else return NO_KEY;



}

void teclado_sw (uint8_t cod_act)
{
	__RW static uint8_t cod_ant = NO_KEY;
	__RW static uint8_t contador = CANT_REBOTES;


	if (cod_act==cod_ant)
	{
		contador--;
		if (!contador)
		{
			buff_key=cod_act;
			contador=CANT_REBOTES;
		}
		return;
	}
	else
	{
		cod_ant=cod_act;
		contador=CANT_REBOTES;
		return;
	}
}

uint8_t Tecla (void)
{
	uint8_t aux=NO_KEY;
	static uint8_t key_ant=NO_KEY;
	if (buff_key==NO_KEY)
	{
		key_ant=buff_key;
		return NO_KEY;
	}
	else if (buff_key!=key_ant)
	{
		key_ant=buff_key;
		return buff_key;
	}
	return NO_KEY;
}


void InitGPIOs_Exp3 ( void )
{
	set_pinsel (A_BCD,PINSEL_GPIO);
	set_pinsel (B_BCD,PINSEL_GPIO);
	set_pinsel (C_BCD,PINSEL_GPIO);
	set_pinsel (D_BCD,PINSEL_GPIO);
	set_pinsel (CLK,PINSEL_GPIO);
	set_pinsel (RST,PINSEL_GPIO);
	set_pinsel (FILA_0,PINSEL_GPIO);
	set_pinsel (FILA_1,PINSEL_GPIO);
	set_pinsel (FILA_2,PINSEL_GPIO);
	set_pinsel (FILA_3,PINSEL_GPIO);
	set_pinsel (COL_0,PINSEL_GPIO);
	set_pinsel (COL_1,PINSEL_GPIO);
	set_pinsel (seg_dp,PINSEL_GPIO);

	set_dir (A_BCD,SALIDA);
	set_dir (B_BCD,SALIDA);
	set_dir (C_BCD,SALIDA);
	set_dir (D_BCD,SALIDA);
	set_dir (CLK,SALIDA);
	set_dir (RST,SALIDA);
	set_dir (COL_0,SALIDA);
	set_dir (COL_1,SALIDA);
	set_dir (FILA_0,ENTRADA);
	set_dir (FILA_1,ENTRADA);
	set_dir (FILA_2,ENTRADA);
	set_dir (FILA_3,ENTRADA);
	set_dir (seg_dp,SALIDA);
}


