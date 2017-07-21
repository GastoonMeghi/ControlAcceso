#include "aplicacion.h"

//void SysTick_Handler(void)
//{
//	barrido_display();
//}
extern __RW uint32_t msgDisplay[6];


void TIMER0_IRQHandler (void)
{

	if (T0IR &(0x01<<4))  //captura0 del timer0
	{
		T0IR &= ~(0x01<<4);
		display(T0CR0);
		msgDisplay[3]|= (0x01<<7); //agrego dp

	}

}

void SysTick_Handler (void)
{



	barrido_display ();



}
