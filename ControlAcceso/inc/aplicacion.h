/*
 * Aplicacion.h
 *
 *  Created on: 14/06/2013
 *      Author: Marcelo
 */

#ifndef APLICACION_H_
#define APLICACION_H_

//----------------------------------------------

//----------------------------------------------
	#include "expansion3.h"
	#include "GPIO.h"
	#include "KitInfo2_BaseBoard.h"
	#include "Oscilador.h"
	#include "RegsLPC1769.h"
	#include "interrupciones.h"
	#include "timers.h"
	#include "systick.h"
	#include "RTC.h"
	#include "prueba.h"

void Inicializar ( void );
void InicPLL     ( void );


/**
 *\def MAX_DIGITIOS
 *\brief cantidad maxima de digitos del codigo personal
 *\details de cambiarse el numero maximo debe modificarse la funcion leer_codigo_personal
 *\details para contemplar un numero distinto de digitos
*/
#define MAX_DIGITOS 4



/**
 *\fn void leer_codigo_personal (uint8_t *digito, uint8_t *buffer_codigo)
 *\brief almacena el codigo personal en buffer_codigo
 *
 *\details cuando el usuario teclea su codigo personal esta funcion lee la variable global key y la almacena en
 *\details buffer_codigo, actualizando el valor de digito, este comienza con un valor igual a MAX_DIGITOS
 *\details y se lo decrementa cada vez que se agrega un nuevo digito, un valor de 0 indica que ya se se guardo
 *\details el codigo por completo
 *\bug no fue testeada
 *
 *\param[in] *digito dir de la variable que contiene el digito del codigo que esta siendo guardado en el buffer
 *\param[in] *buffer_codigo direccion de la variable donde se almacena el codigo
*/
void leer_codigo_personal (uint8_t *digito, uint8_t *buffer_codigo);


#endif /* APLICACION_H_ */
