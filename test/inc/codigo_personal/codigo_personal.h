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



uint8_t get_codigo_personal (uint32_t *codigo_personal);

void capturar_y_mostrar_codigo (void);

uint32_t my_pow (uint8_t base, uint8_t exp);

#endif /* CODIGO_PERSONAL_CODIGO_PERSONAL_H_ */
