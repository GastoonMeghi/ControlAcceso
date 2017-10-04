/**
 \file KitInfo2FW_7Seg.c
 \brief Drivers del display de 7 segmentos
 \details Expansion 2
 \author Ing. Marcelo Trujillo
 \date 2012.04.25
 */

#include "Aplicacion.h"

__RW uint8_t msgDisplay[6];


	void barrido_display(void)
	{
		static uint8_t i = 0;

		set_pin(A_BCD, (msgDisplay[i] & 	  (uint8_t) 0x01) );
		set_pin(B_BCD, (msgDisplay[i]>>1 & (uint8_t) 0x01));
		set_pin(C_BCD, (msgDisplay[i]>>2 & (uint8_t) 0x01));
		set_pin(D_BCD, (msgDisplay[i]>>3 & (uint8_t) 0x01));

		if(!i) { //reseteo al comienzo de cada ciclo
			set_pin (RST, ON);
			set_pin (RST, OFF);
		}
		else {	//produzco el desplazamiento de dígito con un clock
			set_pin (CLK, ON);
			set_pin (CLK, OFF);
		}
		i++;
		i%= DIGITOS;
	}

	//Para evitar blinking, apago (los segmentos) el BCD enviando un código no permitido al CD4511

	//		SetPIN (A_BCD,ON);		//EX3_BCDA = ON ;
	//		SetPIN (B_BCD,ON);		//EX3_BCDB = ON ;
	//		SetPIN (C_BCD,ON);		//EX3_BCDC = ON ;
	//		SetPIN (D_BCD,ON);		//EX3_BCDD = ON ;
	//		SetPIN (seg_dp,OFF);		//EX3_dp = OFF;

	void display (uint32_t val)
	{
		__RW uint8_t i=0;

		for (i=0;i<DIGITOS;i++)
		{
			msgDisplay[i]=val%10;
			val/=10;
		}
	}

	void display_2dsp (uint32_t val, uint8_t dsp)
	{
		__RW uint8_t i=0;

				for (i=0;i<(3+3*dsp);i++)
				{
					msgDisplay[i+3*dsp]=val%10;
					val/=10;
				}
	}
