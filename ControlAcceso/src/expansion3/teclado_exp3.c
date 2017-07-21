/*
 * teclado_exp3.c
 *
 *  Created on: 5 de jun. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"

extern __RW uint8_t buff_key;

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

	if (cod_act==NO_KEY)
	return;

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
	uint8_t aux;
	aux=buff_key;
	buff_key=NO_KEY;
	return aux;
}


void InitGPIOs_Exp3 ( void )
{
	SetPINSEL (A_BCD,PINSEL_GPIO);
	SetPINSEL (B_BCD,PINSEL_GPIO);
	SetPINSEL (C_BCD,PINSEL_GPIO);
	SetPINSEL (D_BCD,PINSEL_GPIO);
	SetPINSEL (CLK,PINSEL_GPIO);
	SetPINSEL (RST,PINSEL_GPIO);
	SetPINSEL (FILA_0,PINSEL_GPIO);
	SetPINSEL (FILA_1,PINSEL_GPIO);
	SetPINSEL (FILA_2,PINSEL_GPIO);
	SetPINSEL (FILA_3,PINSEL_GPIO);
	SetPINSEL (COL_0,PINSEL_GPIO);
	SetPINSEL (COL_1,PINSEL_GPIO);
	SetPINSEL (seg_dp,PINSEL_GPIO);

	SetDIR (A_BCD,SALIDA);
	SetDIR (B_BCD,SALIDA);
	SetDIR (C_BCD,SALIDA);
	SetDIR (D_BCD,SALIDA);
	SetDIR (CLK,SALIDA);
	SetDIR (RST,SALIDA);
	SetDIR (COL_0,SALIDA);
	SetDIR (COL_1,SALIDA);
	SetDIR (FILA_0,ENTRADA);
	SetDIR (FILA_1,ENTRADA);
	SetDIR (FILA_2,ENTRADA);
	SetDIR (FILA_3,ENTRADA);
	SetDIR (seg_dp,SALIDA);
}
