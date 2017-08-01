/*
 * RTC.c
 *
 *  Created on: 22 de jul. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"


void Inic_RTC(void)
{
	RTCILR = 0x00;				// Limpio Flags
	RTCCIIR = 0x00;				// Deshabilito interrupciones
	RTCAMR = 0xFF;				// Enmascaro comparador de alarmas
	RTCCALIBRATION = 0x00;		// Inicializa registro de calibración
	RTCCCR = 0x01;				// Arranca contador
}


void RTC_SetHoraFecha(RTC_HoraFecha* horafecha)
{
	RTCSEC = horafecha->seg;
	RTCMIN = horafecha->min;
	RTCHOUR = horafecha->hora;
	RTCDOM = horafecha->dia_mes;
	RTCDOW = horafecha->dia_semana;
	RTCDOY = horafecha->dia_anio;
	RTCMONTH = horafecha->mes;
	RTCYEAR = horafecha->anio;
}

void RTC_GetHoraFecha(RTC_HoraFecha* horafecha)
{
	horafecha->seg = RTCSEC;
	horafecha->min = RTCMIN;
	horafecha->hora = RTCHOUR;
	horafecha->dia_mes = RTCDOM;
	horafecha->dia_semana = RTCDOW;
	horafecha->dia_anio = RTCDOY;
	horafecha->mes = RTCMONTH;
	horafecha->anio = RTCYEAR;
}


