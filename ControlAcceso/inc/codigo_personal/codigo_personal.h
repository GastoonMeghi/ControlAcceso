/*
 * codigo_personal.h
 *
 *  Created on: 7 de oct. de 2017
 *      Author: Gaston
 */

#ifndef CODIGO_PERSONAL_CODIGO_PERSONAL_H_
#define CODIGO_PERSONAL_CODIGO_PERSONAL_H_

#include "aplicacion.h"
#include "RegsLPC1769.h"

//CAMBIAAAAAAAR DEFINICION DE ENTER!!!!!!!!!!!!!!!!
#define NORMAL 0
#define BUSY 1
#define READY 2
#define TIEMPO_VENCIDO 3
#define PRIMER_PEDIDO 4

/**
 *\fn uint8_t get_codigo_personal (uint32_t *codigo_personal);
 *\brief UI, devuelve el codigo personal ingresado por teclado
 *
 *\details devuelve el estado del codigo BUSY(ingresando codigo), READY (codigo ingresado),TIEMPO_VENCIDO (vencio el tiempo de ingreso de codigo)
 *\details cuando su estado es READY, guarda el codigo personal leido en codigo_personal
 *\details se deben ingresar tantos digitos como MAX_DIGITOS y apretar la tecla ENTER al finalizar para que la funcion devuelva READY

*/
uint8_t get_codigo_personal (uint32_t *codigo_personal);

/**
 *\fn void capturar_y_mostrar_codigo (void);
 *\brief debe ubicarse en la interrupcion del systick, la función lee el teclado y muestra el codigo por el display de 7 segmentos
 *
 *\details utiliza las funciones display y Tecla, con todo lo que ello implica
 *\details se comunica con get_codigo personal por medio de las variables globales definidas
 */
void capturar_y_mostrar_codigo (void);


uint32_t my_pow (uint8_t base, uint8_t exp);
/**
 *\fn void timer_codigo_vencido (void);
 *\brief debe ubicarse en la interrupcion del timer1, informa a las funciones de codigo_personal.c que el timer vencio
*/

void decrementar_timer_codigo (void);
#endif /* CODIGO_PERSONAL_CODIGO_PERSONAL_H_ */
