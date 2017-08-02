/*
===============================================================================
 Name        : ControlAcceso.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "aplicacion.h"
// TODO: insert other include files here

// TODO: insert other definitions and declarations here


__RW uint8_t msgDisplay[6];


/**
 *\var __RW uint8_t flag_ingreso_codigo
 *\brief habilita el ingreso del codigo personal
*/
__RW uint8_t flag_ingreso_codigo;




/**
 *\var __RW unsigned uint32_t buffer_rfid;
 *\brief buffer en el que se guarda el codigo de tarjeta
*/

__RW uint32_t buffer_rfid;

/**
 *\var __RW uint8_t estado=NORMAL;
 *\brief estado del programa, su cambio se realiza en la rutina de interrupcion
*/


__RW uint8_t estado=NORMAL;

/**
 *\var __RW colaborador_t colaborador;
 *\brief almacena la informacion del colaborador leida en la tarjeta para la validacion de la clave personal y el envio a la PC
*/
__RW colaborador_t colaborador;


/**
 *\var __RW uint8_t buff_key
 *\brief buffer donde se almacena la tecla leida en el teclado matricial
*/
__RW uint8_t buff_key;

/**
 *\var __RW datos_pc_t datos_pc;
 *\brief  almacena la informacion enviada por la PC
*/

__RW datos_pc_t datos_pc;

/**
 *\var __RW uint16_t timer_codigo_personal
 *\brief  setea un tiempo maximo para el ingreso del codigo
 *\details un valor mayor a cero indica que el timer esta corriendo
 *\details un valor igual a cero indica que el timer vencio
 *\details un valor de -1 indica que el timer esta desactivado
*/

__RW uint16_t timer_codigo_personal = -1;


int main(void) {

	Inicializar ( );

    //prueba ();

    while (1)
    aplicacion ();

    return 0 ;
}
