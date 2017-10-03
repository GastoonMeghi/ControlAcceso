/*
 * wav.h
 *
 *  Created on: 17 de set. de 2017
 *      Author: Gaston
 */

#ifndef WAV_WAV_H_
#define WAV_WAV_H_


#include "aplicacion.h"


//estados de las funciones
#define INIC 0
#define REPRODUCCION 1
#define NORMAL 2
#define POP 3
#define READ 4
#define ULTIMO 5
#define TERMINE 6
#define POP_COLA 7

//codigos de wavs
#define WAV_BIENVENIDO 1
#define WAV_HASTA_LUEGO 2
#define WAV_CLAVE_INCORRECTA 3
#define WAV_CLAVE_CORRECTA 4
#define WAV_INGRESE_CODIGO 5
#define NO_WAV 0

#define TAM_BUFF_REPRODUCCION 100
#define CANT_WAVS 5


typedef unsigned char FIL;


/**
 *\fn void bzero (unsigned int *array,unsigned int tam);
 *\brief inicializa los elementos de un array en 0 (NO_WAV que es lo mismo)
 *
 *\details se usa para limpiar la cola de reproduccion en void reproducir_wav (__RW uint32_t wav);
 *\details es de uso interno de wav.c
 *
 *\param[in] *array vector a incializar
 *\param[in] *tam tamaño del vector
*/
void bzero (unsigned int *array,unsigned int tam);


/**
 *\fn void reproducir_wav (__RW uint32_t wav);
 *\brief parte de la interfaz de usuario, en cola el wav que se pasa como parametro en la lista de reproduccion
 *
 *\details llamar dos veces a esta funcion con el mismo wav ocaciona que se reproduzca dos veces, la cantidad maxima de wavs en espera esta dada por CANT_WAVS+5
 *\details si se agregan wavs, debe modificarse esta cantidad,agregar su codigo en wav.h y contemplarlo en la funcion WAV_TO_DAC
 *\param[in] *wav codigo de wav a reproducir (ver wav.h)
*/
void reproducir_wav (uint32_t wav);


/**
 *\fn int leer_buff_reproduccion (FIL *wav);
 *\brief uso interno de wav.c, reproduce el archivo que es pasado como parametro, devuelve 1 en caso de terminar, 0 en caso de seguir reproduciendo
 *\details LA FUNCION SUPONE QUE: wav ES UN ARCHIVO DE TIPO WAV, QUE FUE ABIERTO MEDIANTE FOPEN, QUE SE REALIZO EL FMOUNT,Y QUE SE POSICIONO EN LA SECCION DE DATOS
*\param[in] *wav puntero a estructura de archivo fatfs del wav a reproducir.
*/
int leer_buff_reproduccion (FIL *wav);


/**
 *\fn void WAV_TO_DAC (void);
 *\brief se coloca dentro de una interrupcion de un timer, debe ser llamada cada 44,44 useg, debido a la frecuencia de sample que utilizan estos wavs
 *\details esta funcion es la encargada de tomar la cola de reproduccion y reproducir cada wav hasta terminar
*/
void WAV_TO_DAC (void);


/**
 *\fn void inic_wav (void);
 *\brief inicializa la cola de reproduccion en NO_WAV, y realiza el fmount
 *\details DEBE SER LLAMADA ANTES DE ACTIVAR LA INTERRUPCION QUE LLAMA A WAV_TO_DAC, de no ser asi, podrian reproducirse wavs que no correspondan
*/

void inic_wav (void);

#endif /* WAV_WAV_H_ */
