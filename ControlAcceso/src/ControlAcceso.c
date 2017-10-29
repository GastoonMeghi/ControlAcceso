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
 *\var __RW colaborador_t colaborador;
 *\brief almacena la informacion del colaborador leida en la tarjeta para la validacion de la clave personal y el envio a la PC
*/
__RW colaborador_t colaborador;



/**
 *\var __RW datos_pc_t datos_pc;
 *\brief  almacena la informacion enviada por la PC
*/


__RW datos_pc_t datos_pc;


__RW unsigned int DAC_buff;
/**
 *\var __RW uint16_t timer_codigo_personal
 *\brief  setea un tiempo maximo para el ingreso del codigo
 *\details un valor mayor a cero indica que el timer esta corriendo
 *\details un valor igual a cero indica que el timer vencio
 *\details un valor de -1 indica que el timer esta desactivado
*/

__RW uint16_t timer_codigo_personal = -1;



////!!!!!!!CAMBIAR AL SALIR DEL MODO DE PRUEBA
/*

 * aplicacion linea 149 colaborador.codigo_personal=0;
 * aplicacion linea 150 colaborador.codigo_tarjeta=0;
 */


//extern char SD[];

int main(void) {

//	uint32_t i;
	Inicializar ( );
//	colaborador.codigo_tarjeta=0;
//
//prueba ();
//
//


	//LA SD SE MONTA DESDE void inic_wav (void)

    while (1)
    {
    	reproducir_wav (WAV_BIENVENIDO);

   // 	reproducir_wav (WAV_BIENVENIDO);
    	//if (get_codigo_personal (&i)==READY)
    	//reproducir_wav (WAV_BIENVENIDO);
   // 	ejemplo_uart1();

    }

    return 0 ;
}
