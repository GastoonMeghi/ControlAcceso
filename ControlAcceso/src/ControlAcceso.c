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




int main(void) {

	Inicializar ( );

    while (1)
    {
    	aplicacion ();
    }

    return 0 ;
}
