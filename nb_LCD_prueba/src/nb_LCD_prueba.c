/*
===============================================================================
 Name        : nb_LCD_prueba.c
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

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

    // TODO: insert code here

    // Force the counter to be placed into memory
    volatile static int i = 0 ;
    // Enter an infinite loop, just incrementing a counter
    inic_GPIO ();
    InicPLL ();
    Inic_LCD();

    inic_systick ();
    nb_Display_lcd("HOLAAAA",0,0);
    while(1) {
        i++ ;
    }
    return 0 ;
}
