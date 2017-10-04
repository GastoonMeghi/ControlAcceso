#include "aplicacion.h"


extern __RW uint8_t timer=1; //flag que controla el tiempo maximo de ingreso de codigo

void TIMER0_IRQHandler (void)
{
	WAV_TO_DAC ();
	T0IR|=(0x01);
}


void TIMER0_IRQHandler (void)
{
	timer=0; //vencio el tiempo establecido
	T1IR|=(0x01); //limpio flag de interrupcion
}

