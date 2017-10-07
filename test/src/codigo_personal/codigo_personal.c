/*
 * codigo_personal.c
 *
 *  Created on: 7 de oct. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"
#include "definiciones_codigo_personal.h"

__RW uint32_t codigo=0;

__RW uint8_t resultado=BUSY;

__RW uint8_t habilitar=0;

__RW uint8_t timer_ingreso_codigo;

void capturar_y_mostrar_codigo (void)
{
	static __RW uint8_t inic=1;
	static __RW uint8_t digito;
	__RW uint8_t tecla;

	if (!habilitar) //si no se activo la captura de cogido desde get_codigo_personal
	{
		resultado = BUSY;
		return;
	}

	if (inic)
	{
		codigo =0;
		digito =0;
		resultado=BUSY;
		ACTIVAR_TIMER_INGRESO_CODIGO;
		timer_ingreso_codigo=1;
		inic=0;
	}

	if (!timer_ingreso_codigo) //vencio el tiempo estipulado
	{
		codigo =0;
		digito =0;
		resultado=TIEMPO_VENCIDO;
		inic=1;
		habilitar=0;
		display (0);
		return;
	}
	tecla =Tecla();

	if (tecla==ENTER)
	{
		resultado=READY;
		habilitar =0;
	    display (0);
		inic=1;
		return;
	}
	if (tecla<0 ||tecla>9) //tecla invalida
	{
		resultado=BUSY;
		return;
	}
	if (digito>=MAX_DIGITOS) //esto impide que el usuario ingrese un codigo mayor al maximo estipulado, cuando se alcanza el máx de digigos
	{						 //las formas de salir de este modo son o esperando a que termine el timer de ingreso o presionando enter
		resultado=BUSY;
		return;
	}
	codigo*=10;
	codigo+=tecla;
	display(codigo);
	digito++;
	resultado=BUSY;
	return;
}

uint8_t get_codigo_personal (uint32_t *codigo_personal)
{
	static __RW uint8_t estado=PRIMER_PEDIDO;


	if (estado==PRIMER_PEDIDO)
	{
		habilitar=1; //habilito a capturar y mostrar codigo
		*codigo_personal=0; //inicializo
		estado=NORMAL;
		resultado= BUSY;
	}
	if (estado==NORMAL)
	{
		if (resultado==READY) //si capturar_y_mostrar_codigo termino
		{
			*codigo_personal=codigo; //devuelvo el codigo capturado
			estado = PRIMER_PEDIDO;  // me pongo a la espera de un nuevo pedido
			resultado =BUSY;
			return READY;
		}
	}
	return resultado;
}
