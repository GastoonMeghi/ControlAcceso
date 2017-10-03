#include "aplicacion.h"


void TIMER0_IRQHandler (void)
{
	WAV_TO_DAC ();
	T0IR|=(0x01);
}


