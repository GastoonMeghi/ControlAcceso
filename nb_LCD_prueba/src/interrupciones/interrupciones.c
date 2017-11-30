#include "aplicacion.h"




void SysTick_Handler (void)
{

	nb_driver_LCD ();
	update_Display();

}

