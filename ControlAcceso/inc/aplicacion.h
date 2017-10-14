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
	#include "string.h"
	#include "expansion3.h"
	#include "GPIO.h"
	#include "KitInfo2_BaseBoard.h"
	#include "codigo_personal.h"
	#include "Oscilador.h"
	#include "RegsLPC1769.h"
	#include "interrupciones.h"
	#include "timers.h"
	#include "systick.h"
	#include "RTC.h"
	#include "prueba.h"
	#include "dac.h"
	#include "wav.h"
	#include "fatfs.h"
	#include <UART1/UART1.h>
	void Inicializar ( void );
void InicPLL     ( void );


/**
 *\def MAX_DIGITIOS
 *\brief cantidad maxima de digitos del codigo personal
 *\details de cambiarse el numero maximo debe modificarse la funcion leer_codigo_personal
 *\details para contemplar un numero distinto de digitos
*/

#define CODIGO_PC_RECIBIDO datos_pc.codigo_personal!=0
#define CODIGO_CORRECTO datos_pc.codigo_personal == colaborador.codigo_personal
#define HAY_TARJETA colaborador.codigo_tarjeta!=0
#define DESACTIVAR_TEMPORIZADOR_DE_INGRESO timer_codigo_personal = -1;
#define TIEMPO_DE_INGRESO_CODIGO_PERSONAL  27000
#define ACTIVAR_TEMPORIZADOR_DE_INGRESO timer_codigo_personal = TIEMPO_DE_INGRESO_CODIGO_PERSONAL
#define TEMPORIZADOR_DE_INGRESO_VENCIDO timer_codigo_personal ==0

#define NORMAL 0
#define DETECCION 1
#define SETEO 2
#define INGRESO_CODIGO 3
#define VALIDACION_CODIGO 4




typedef struct
{
	__RW uint32_t codigo_personal;
	__RW uint8_t horario_entrada;
	__RW uint32_t codigo_tarjeta;

} colaborador_t;

typedef struct
{
	__RW uint32_t codigo_personal;
	__RW uint32_t codigo_tarjeta;
	__RW uint8_t dia;
	__RW uint8_t mes;
	__RW uint8_t anio;
	__RW uint8_t hora;
	__RW uint8_t min;
	__RW uint8_t accion; //ENTRADA O SALIDA
} datos_pc_t;


/**
 *\fn void leer_codigo_personal (uint8_t *buffer_codigo)
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
void leer_codigo_personal (uint32_t *buffer_codigo);



/**
 *\fn void inic_datos (void)
 *\brief inicializa los datos utilizados en la aplicacion
*/

void inic_datos (void);


/**
 *\fn void estado_normal (void)
 *\brief modo de trabajo normal del control de acceso
 *\details realiza las tareas de deteccion de tarjeta, ingreso de codigo personal
 *\details verificacion del mismo y envio de estos a la pc
*/

void estado_normal (void);

/**
 *\fn void estado_seteo (void);
 *\brief modo de trabajo de seteo del control de acceso
 *\details realiza las tareas de ingreso de tarjeta y codigo personal al sistema
 *\details
*/

void estado_seteo (void);

void ejemplo_uart1 ();	// Funcion a modo de ejemplo

void aplicacion (void);
#endif /* APLICACION_H_ */
