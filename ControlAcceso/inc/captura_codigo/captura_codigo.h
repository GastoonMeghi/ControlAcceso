/*
 * captura_codigo.h
 *
 *  Created on: 3 de oct. de 2017
 *      Author: Gaston
 */

#ifndef CAPTURA_CODIGO_CAPTURA_CODIGO_H_
#define CAPTURA_CODIGO_CAPTURA_CODIGO_H_

#define INICIAR_TIMER T1TCR |= (0x01<<0);timer=1;
#define TIEMPO_MAX_INGRESO 20 //segundos

#define INICIO 0
#define TIEMPO_VENCIDO 1
#define CODIGO_CAPTURADO 2
#define BUSY 3

#define MAX_DIGITOS 4

/**
 *\fn void capturar_codigo(void);
 *\brief guarda las teclas presionadas en un buffer, es activada por get_codigo_personal, limita el tiempo de ingreso de codigo
 *
 *\details de uso interno de captura_codigo.c, es activada por get_codigo_personal, esta función inicia un timer para
 *\details limitar el tiempo de ingreso de codigo, va cargando los digitos en la variable codigo_personal
 *\details que es exclusiva de uso interno, e informa su desarrollo a get_codigo_personal por medio de la variable
 *\details resultado_captura, los valores posibles de la misma son explicados en su descripción.
 *\details debe estar dentro de la interrupcion del systick
*/

void capturar_codigo(void);



/**
 *\fn int get_codigo_personal(uint32_t &codigo);
 *\brief interfaz de usuario,pide el codigo personal y se informa por medio del valor de retorno
 *\details Los valores de retorno posibles son: BUSY (todavia no se termino de ingresar el codigo), TIEMPO_VENCIDO (el tiempo de ingreso se vencion),CODIGO_CAPTURADO (se logro capturar el codigo deseado)
*\param[in] *codigo puntero a la direccion de memoria donde se desea guardar el codigo obtenido, NO VERIFICADO
*/
int get_codigo_personal(uint32_t *codigo);



uint32_t pow (uint8_t base, uint8_t exponente);



#endif /* CAPTURA_CODIGO_CAPTURA_CODIGO_H_ */
