/**
 	\file AP_Mensajes.c
 	\brief Aplicacion para conectar con el software provisto por la catedra
 	\details Manejo del hardware del kit y RX/TX con la PC
 	\author Pablo Irrera Condines
 	\date 2013.05.08
*/

#include <stdio.h>
#include <string.h>
#include "PR_Serie.h"
#include "AP_Mensajes.h"

extern char ESTADO_RX_UART0;
#define TARJETA 'T'
#define NUEVA_TARJETA 'Z'
#define TARJETA_CODIGO_CORRECTO 'B'
#define TARJETA_CODIGO_INCORRECTO 'M'
#define TARJETA_GUARDADA'G'

void MensajesRX(void)
{
   	uint8_t dato;
   	static uint8_t espera = 0;

   	if( !PopRx_0(&dato) )
   	{
   		switch(espera)
   		{
			case 0: 				// Espera de mensaje
				espera = dato;		// ID del mensaje
	    		switch (espera)
				{

					case TARJETA:    // Z
					case NUEVA_TARJETA:// EL USUARIO PIDIO UNA NUEVA TARJETA
					case TARJETA_CODIGO_CORRECTO:  // B
					case TARJETA_CODIGO_INCORRECTO://M
						break;
					default:
						espera = 0;
						break;
			   	}


	    		break;

			case TARJETA:// EL USUARIO PIDIO UNA NUEVA TARJETA
				Transmitir_TARJETA();
				espera = 0;

				break;



			case NUEVA_TARJETA:// EL USUARIO PIDIO UNA NUEVA TARJETA
							Transmitir_TARJETA_INGRESO();
							espera = 0;

							break;


			case TARJETA_CODIGO_CORRECTO:  // B
				ESTADO_RX_UART0='B';
				espera=0;
				break;


			case TARJETA_CODIGO_INCORRECTO://M
				ESTADO_RX_UART0='M';
				espera = 0;
				break;

		/*	case TARJETA_GUARDADA://M
					ESTADO_RX_UART0='G';
					espera = 0;
					break;
*/

			default:
			//	ESTADO_RX_UART0='0';
			//	espera = 0;
				break;




		}
	}
}


void Transmitir_TARJETA(void)// TARJETA QUE ESTA EN LA BASE DE DATOS
{
	ESTADO_RX_UART0='K';


}

void Transmitir_TARJETA_INGRESO(void)// TARJETA NUEVA
{
	ESTADO_RX_UART0='Z';
}


