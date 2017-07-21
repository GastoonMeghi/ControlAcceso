
#include "Aplicacion.h"

void Inicializar ( void )
{
	//inic_GPIO ();
	InicPLL ();
	inic_timer0 ();
	Inicializar_Display7s( );
	inic_systick ();

}
