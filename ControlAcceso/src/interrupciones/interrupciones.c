#include "aplicacion.h"


void TIMER0_IRQHandler (void)
{
	WAV_TO_DAC ();
	T0IR|=(0x01);
}


void TIMER1_IRQHandler (void)
{
	timer_codigo_vencido ();
	T1IR|=(0x01);
}
