/*
 * prueba.c
 *
 *  Created on: 22 de jul. de 2017
 *      Author: Gaston
 */

#include "aplicacion.h"

void prueba (void)
{
	__RW uint32_t dato; // fecha mostrada en el formato DDMMAA

	RTC_HoraFecha fecha_test;   //fecha del rtc

	//inicializo en mi cumple
	fecha_test.seg =0;
	fecha_test.min =0;
	fecha_test.hora=0;
	fecha_test.dia_mes=24;
	fecha_test.mes=3;
	fecha_test.anio=1997;

	//seteo el RTC con la fecha
	RTC_SetHoraFecha(&fecha_test);


	while (1)
	{
		dato =obtener_dato ();
		display (dato);


	}
}

uint32_t obtener_dato (void) //presenta el dato de la forma DDMMAA
{
	RTC_HoraFecha aux;
	uint32_t dato=0;

	RTC_GetHoraFecha(&aux);

	dato+= aux.anio%10; //obtengo el primer digito del año
	aux.anio/=10; //elimino el primer digito
	dato+= (aux.anio%10)*10; //obtengo el segundo digito del año
	dato+= (aux.mes)*100; //obtengo el mes
	dato+= (aux.dia_mes)*10000; //obtengo el dia
	return dato;
}
