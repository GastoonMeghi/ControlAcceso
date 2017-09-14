#include "aplicacion.h"



extern __RW uint16_t wav;
extern __RW unsigned int DAC_buff;

extern __RW uint8_t reproduciendo;

extern __RW uint32_t msgDisplay[6];

extern __RW uint16_t timer_codigo_personal;

extern __RW uint8_t flag_ingreso_codigo;

extern __RW colaborador_t colaborador;



void SysTick_Handler (void)
{
	barrido_display ();
	teclado_sw(teclado_hw());
	display(colaborador.codigo_personal);
	//display (123456);
	if (flag_ingreso_codigo)
	{
		leer_codigo_personal(&(colaborador.codigo_personal));

	}

	if (timer_codigo_personal>0)
	{
		timer_codigo_personal--;
	}

}


void TIMER0_IRQHandler (void)
{
	T0IR |=0x01;

	if (reproduciendo==1)
	{
		reproducir_wav (wav,reproduciendo);
		escribir_dac (DAC_buff);
	}

}
