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
 *\var __RW uint8_t buff_key
 *\brief buffer donde se almacena la tecla leida en el teclado matricial
*/
__RW uint8_t buff_key;

int main(void) {

	Inicializar ( );

    prueba ();

    while (1)
    aplicacion ();

    return 0 ;
}
