/*
 * codigo_personal.c
 *
 *  Created on: 7 de oct. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"
#include "definiciones_codigo_personal.h"
/**
 *\file codigo_personal.c
 *\brief funciones encargadas de la captura y muestra del codigo por el display
 *
 *\details Las funciones dependen de:
 *\details la cantidad maxima de digitos del codigo
 *\details la implementacion de la funciones Tecla y display
 *\details la configuracion del systick y el timer1
 *\details de los codigos asignados a las teclas
 *\bugs cambiar la definicion del ENTER
 *
 *\param[in] *array vector a incializar
 *\param[in] *tam tamaño del vector
*/



/**
 *\var __RW uint32_t codigo=0;
 *\brief  uso interno de codigo_personal.c, es el codigo leido en el teclado
*/
__RW uint32_t codigo=0;
/**
 *\var __RW uint8_t resultado
 *\brief  uso interno, resultados de las funciones de codigo_personal.c
 *\details valores posibles: BUSY(ingresando codigo), READY (codigo ingresado),TIEMPO_VENCIDO (vencio el tiempo de ingreso de codigo)
*/
__RW uint8_t resultado=BUSY;

/**
 *\var __RW uint8_t habilitar;
 *\brief  uso interno, variable que habilita el funcionamiento de void capturar_y_mostrar_codigo (void)
*/
__RW uint8_t habilitar=0;
/**
 *\var __RW uint8_t timer_ingreso_codigo;
 *\brief  uso interno, flag que indica el estado del timer, 0: vencido, 1:corriendo
*/

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
		//display (0);
		return;
	}
	//tecla =Tecla();
	tecla = 5;

	if (tecla==ENTER)
	{
		resultado=READY;
		habilitar =0;
		//display (0);
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
	//display(codigo);
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


void timer_codigo_vencido (void)
{
	timer_ingreso_codigo=0;
}
