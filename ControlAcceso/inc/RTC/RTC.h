/*
 * RTC_firmware.h
 *
 *  Created on: 22 de jul. de 2017
 *      Author: Gaston
 */

#ifndef RTC_RTC_H_
#define RTC_RTC_H_

#include "aplicacion.h"


#define RTC_INTERRUPCION_SEG		0
#define RTC_INTERRUPCION_MIN		1
#define RTC_INTERRUPCION_HORA		2
#define RTC_INTERRUPCION_DIAMES		3
#define RTC_INTERRUPCION_DIASEM		4
#define RTC_INTERRUPCION_DIAANIO	5
#define RTC_INTERRUPCION_MES		6
#define RTC_INTERRUPCION_ANIO		7

typedef struct {
	uint32_t seg;
	uint32_t min;
	uint32_t hora;
	uint32_t dia_mes;
	uint32_t dia_semana;
	uint32_t dia_anio;
	uint32_t mes;
	uint32_t anio;
} RTC_HoraFecha;

// Prototipos
void Inic_RTC(void);
void RTC_HabilitaInterrupcion(uint32_t);
void RTC_SetHoraFecha(RTC_HoraFecha*);
void RTC_GetHoraFecha(RTC_HoraFecha*);



#endif /* RTC_RTC_H_ */
