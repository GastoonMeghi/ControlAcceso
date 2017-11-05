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
	disk_timerproc();	/* Disk timer process */
	barrido_display ();
	teclado_sw(teclado_hw());
	capturar_y_mostrar_codigo ();
	update_RFID();
	update_Display();
}

extern uint8_t uart_timeout;

void UART1_IRQHandler (void)
{
	uint8_t iir;
	iir = U1IIR;			//IIR es reset por HW, una vez que lo lei se resetea.
	if ( iir & 0x04 /*&& !uart_timeout*/)		//Data ready
	{
		PushRx((uint8_t )U1RBR );
		uart_timeout = 1000;
	}
}
