#include "aplicacion.h"

extern __RW uint8_t timer_ingreso_codigo;

void TIMER0_IRQHandler (void)
{
	WAV_TO_DAC ();
	T0IR|=(0x01);
}


void TIMER1_IRQHandler (void)
{
	timer_ingreso_codigo=0;
	T1IR|=(0x01);
}
