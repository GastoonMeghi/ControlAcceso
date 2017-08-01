
#include "Aplicacion.h"

void Inicializar ( void )
{
	inic_GPIO ();
	InicPLL ();
	inic_timer0 ();
	InitGPIOs_Exp3 ();
	inic_systick ();
	Inic_RTC ();

}

void aplicacion (void)
{
	__RW uint8_t estado=NORMAL;

	while (1)
	{

		if (estado==NORMAL)
		{

		}
	}

}


void leer_codigo_personal (uint8_t *digito, uint8_t *buffer_codigo)
{
	if (*digito<=0) //si por accidente se va de rango sale de la funcion sin hacer nada
		return;

	if (*digito==1)
	*buffer_codigo += buff_key;

	else if (*digito==2)
	*buffer_codigo += buff_key*10;

	else if (*digito==3)
	*buffer_codigo += buff_key*100;

	else if (*digito==4)
	*buffer_codigo += buff_key*1000;

	(*digito)--;

}
