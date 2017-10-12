#include "aplicacion.h"


void TIMER0_IRQHandler (void)
{


	WAV_TO_DAC ();
//	static uint8_t aux=0;
//	if (aux==0)
//	{
//		DACR&= ~(0x3FF<<6);
//		aux=1;
//	}
//	else
//	{
//		DACR|= (0x3FF<<6);
//		aux=0;
//	}
	T0IR|=(0x01);
}


void TIMER1_IRQHandler (void)
{
	timer_codigo_vencido ();
	T1IR|=(0x01);
}

void SysTick_Handler (void)
{
	barrido_display ();
	teclado_sw(teclado_hw());
	capturar_y_mostrar_codigo ();
}
