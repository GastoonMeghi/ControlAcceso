#include "aplicacion.h"
extern uint8_t soft_timer;

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



void SysTick_Handler (void)
{
	disk_timerproc();	/* Disk timer process */
	barrido_display ();
	nb_driver_LCD ();
	teclado_sw(teclado_hw());
	capturar_y_mostrar_codigo ();
	update_RFID();
	update_Display();
	decrementar_timer_codigo ();
	if (soft_timer) soft_timer--;
}

void UART1_IRQHandler (void)
{
	uint8_t iir;
	iir = U1IIR;			//IIR es reset por HW, una vez que lo lei se resetea.
	if ( iir & 0x04 )		//Data ready
	{
		PushRx((uint8_t )U1RBR );
	}
}
