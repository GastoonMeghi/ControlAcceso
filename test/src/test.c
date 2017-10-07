/*
===============================================================================
 Name        : test.c
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

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    set_pinsel (3,26,0);
    set_dir (3,26,1);
    set_pinmodeOD (3,26,0);
    inic_timer1();
    T1TCR |= (0x01<<0);
    get_codigo_personal (&i);
    while(1) {
    	capturar_y_mostrar_codigo ();
        i++ ;
    }
    return 0 ;
}
