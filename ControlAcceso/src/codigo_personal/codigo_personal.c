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

__RW uint8_t resultado_leido=1;//flag que evita que capturar y mostrar codigo sobre escriba un resultado que todavia no fue informado a la aplicacion

__RW uint8_t habilitar=0;


__RW uint32_t timer_ingreso_codigo;

void capturar_y_mostrar_codigo (void)
{
	static __RW uint8_t inic=1;
	static __RW uint8_t digito;
	__RW uint8_t tecla;


	if (resultado_leido) //evito sobrescribir un resultado que no fue leido todavia, la variable se pone en uno, en get_codigo_personal, que es donde se informa el resultado
	{
		resultado_leido =0;
	}
	else return;


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
		timer_ingreso_codigo=200000;
		inic=0;
	}

	if (timer_ingreso_codigo <= 0) //vencio el tiempo estipulado
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

	if (tecla==ENTER && digito==MAX_DIGITOS)
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
	codigo+=tecla*my_pow(10,digito);
	display(codigo);
	digito++;
	resultado=BUSY;
	return;
}

uint8_t get_codigo_personal (uint32_t *codigo_personal)
{
	static __RW uint8_t estado=PRIMER_PEDIDO;

	__RW uint8_t resultado_auxiliar; //esta variable evita que al poner resultado_leido=1, el sistick interrumpa justoo despues y cambie su valor (me voy de mambo en paranoico)



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
			resultado_leido=1; //informo a capturar y mostrar codigo, que lei el resultado y puede actualizarlo
			return READY;
		}
		if (resultado==TIEMPO_VENCIDO)
		{
			estado=PRIMER_PEDIDO;
			resultado = BUSY;
			resultado_leido=1;
			return TIEMPO_VENCIDO;
		}
	}
	resultado_auxiliar = resultado;
	resultado_leido=1; //informo a capturar y mostrar codigo, que lei el resultado y puede actualizarlo

	return resultado_auxiliar;
}


uint32_t my_pow (uint8_t base, uint8_t exp)
{
	uint8_t aux;
	if (exp==0) return 1;
	if (exp==1) return base;
	for (aux=1;aux<exp;aux++)
		base*=base;
	return base;

}

void decrementar_timer_codigo (void)
{
	if (timer_ingreso_codigo) timer_ingreso_codigo--;
}
