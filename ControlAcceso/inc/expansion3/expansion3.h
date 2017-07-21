/*
 * expansion3.h
 *
 *  Created on: 5 de jun. de 2017
 *      Author: Gaston
 */

#ifndef INC_EXPANSION3_EXPANSION3_H_
#define INC_EXPANSION3_EXPANSION3_H_

	#include "aplicacion.h"
	#include "RegsLPC1769.h"

	/** -------------------------------------------------------------------------------------
	 *PLACA EXPANSION 3
	 */
	//!< Display
	#define		A_BCD			EXPANSION0
	#define		B_BCD			EXPANSION1
	#define		C_BCD			EXPANSION2
	#define		D_BCD			EXPANSION3
	#define		seg_dp			EXPANSION4


	#define		RST				EXPANSION6
	#define		CLK				EXPANSION5


	#define		DIGITOS			6

	#define		DSP0			0			//!< Display rojo
	#define		DSP1			1


	// teclado  EXPANSION3
	//---definición de HW
	#define COL_0           EXPANSION11	//PORT3,25// PLACA EXPANSION 3
	#define COL_1           EXPANSION12	//PORT1,27// PLACA EXPANSION 3
	#define FILA_0          EXPANSION7	//PORT1,25// PLACA EXPANSION 3
	#define FILA_1          EXPANSION8	//PORT1,22// PLACA EXPANSION 3
	#define FILA_2          EXPANSION9	//PORT1,19// PLACA EXPANSION 3
	#define FILA_3          EXPANSION10	//PORT0,20// PLACA EXPANSION 3
	//---
	//---Acceso al HW
	#define		EX3_fila0			get_pin(FILA_0,ACTIVO_ALTO)
	#define		EX3_fila1			get_pin(FILA_1,ACTIVO_ALTO)
	#define		EX3_fila2			get_pin(FILA_2,ACTIVO_ALTO)
	#define		EX3_fila3			get_pin(FILA_3,ACTIVO_ALTO)

	#define		EX3_columna0_OFF	set_pin(COL_0,ACTIVO_BAJO)
	#define		EX3_columna0_ON 	set_pin(COL_0,ACTIVO_ALTO)
	#define		EX3_columna1_OFF    set_pin(COL_1,ACTIVO_BAJO)
	#define		EX3_columna1_ON 	set_pin(COL_1,ACTIVO_ALTO)
	//---

	#define 	CANT_REBOTES	5 //valor empírico
	#define		REPOSO			0
	#define		CHEQUEO			1
	#define		CAMBIO			2
	#define		EMERGENCIA		CAMBIO
	#define		NO_KEY			(uint8_t) 0xFF


	/** -------------------------------------------------------------------------------------
	 * Prototipos
	 */



void barrido_display(void);

void display (uint32_t val);

uint8_t teclado_hw (void);

void teclado_sw (uint8_t cod_actual);

void display_2dsp (uint32_t val, uint8_t dsp);

void InitGPIOs_Exp3 ( void );


uint8_t Tecla (void);




#endif /* INC_EXPANSION3_EXPANSION3_H_ */
