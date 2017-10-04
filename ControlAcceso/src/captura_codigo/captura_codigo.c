/*
 * captura_codigo.c
 *
 *  Created on: 3 de oct. de 2017
 *      Author: Gaston
 */

#include "aplicacion.h"


/**
 *\var __RW uint32_t codigo_personal=0;
 *\brief variable de uso interno de captura_codigo.c,almacena el codigo personal, segun se va ingresando
*/
__RW uint32_t codigo_personal=0;

/**
 *\var __RW uint8_t resultado_captura;
 *\brief variable de uso interno de captura_codigo.c,almacena el progreso de la captura del codigo
 *\details sus valores posibles son BUSY (el codigo esta siendo capturado), TIEMPO_VENCIDO (vencio el tiempo de ingreso de codigo)
 *\details CODIGO_CAPTURADO (se logro capturar el codigo)
*/
__RW uint8_t resultado_captura=BUSY;
/**
 *\var __RW uint8_t habilitar_captura;
 *\brief variable de uso interno de captura_codigo.c,controla si se deben capurar las teclas o no
 *\details de ser cero, capturar_codigo esta inhabilitada, de ser uno esta habilitada
*/
__RW uint8_t habilitar_captura;


__RW uint8_t timer=1;

int get_codigo_personal(uint32_t *codigo)
{
	static uint32_t estado=PRIMER_PEDIDO;

	switch (estado)
	{
	case PRIMER_PEDIDO:
		habilitar_captura=1;
		INICIAR_TIMER;
		estado=CAPTURAR;
	case CAPTURAR:
		if (resultado_captura==CODIGO_CAPTURADO)
		{
		 *codigo=codigo_personal;
		 resultado_captura=BUSY;
		 estado=PRIMER_PEDIDO;
		 return CODIGO_CAPTURADO;
		}
		return resultado_caputura; //puede ser BUSY o TIEMPO_VENCIDO

	}
}


void capturar_codigo(void)
{
	static uint8_t estado=INICIO;
	static uint8_t digito=0;
	static uint32_t codigo;
	uint8_t aux;

	if(!habilitar_captura)
	{
	 resultado_captura= BUSY;
	 return;
	}


	if (estado==INICIO)
	{	digito=0;
		codigo=0;
		INICIAR_TIMER;
		estado=CAPTURANDO;

	}

	if (estado==CAPTURANDO)
	{
		if (!timer) //vencio el tiempo
		{
		estado=INICIO;  //reseteo valores
		habilitar_caputura=0; //inhabilito la funcion, hasta ser llamada por get_codigo_personal
		resultado_captura= TIEMPO_VENCIDO; //informo condicion a get_codigo personal
		return;
		}

		if(digito<MAX_DIGITOS)
		{
		resultado_captura= BUSY;
		aux=Tecla();
		if (aux<0||aux>9)return; //tecla invalida, no se contabiliza
		codigo+= aux*pow (10,digito++); //lo calcula y despues incrementa el digito
		return;
		}
		else  //se ingreso el maximo de digitos
		{
		 resultado_caputura=CODIGO_CAPTURADO;
		 habilitar_caputra=0;
		 codigo_personal=codigo;
		 estado=INICIO;
		 return;
		}


	}

}




uint32_t pow (uint8_t base, uint8_t exponente)
{
uint8_t aux;
uint32_t res=base;

if (exponente==0) return 1;


for (aux=1;aux<exponente;aux++)
res=*base;

return res;
}
