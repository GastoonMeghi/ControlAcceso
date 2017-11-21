/*
 * AP_Mensajes.h
 *
 *  Created on: 09/07/2013
 *      Author: Pablo
 */

#ifndef AP_MENSAJES_H_
#define AP_MENSAJES_H_

// ID de los mensajes
#define MSG_EXPANSION					'E'
#define MSG_LCD_SUPERIOR				'1'
#define MSG_LCD_INFERIOR				'2'
#define MSG_LEDS_RELAYS					'3'
#define MSG_RGB_BUZZER					'4'
#define MSG_DISPLAY_DERECHA				'5'
#define	MSG_DISPLAY_IZQUIERDA			'6'
#define	MSG_DAC							'7'
#define	MSG_LEDS						'8'
#define	MSG_DISPLAY_MATRICIAL_VALOR		'9'
#define	MSG_DISPLAY_MATRICIAL_ROTACION	'A'
#define	MSG_RTC							'0'

// Funciones del teclado 2x4 (expansion 3)
#define EX3_F0	0
#define EX3_F1	4
#define EX3_F2	1
#define EX3_F3	5
#define EX3_F4	2
#define EX3_F5	6
#define EX3_F6	3
#define EX3_F7	7

// Funciones del teclado 3x3 (expansion 4)
#define EX4_F0	0
#define EX4_F1	3
#define EX4_F2	6
#define EX4_F3	1
#define EX4_F4	4
#define EX4_F5	7
#define EX4_F6	2
#define EX4_F7	5
#define EX4_F8	8

//Timers y eventos
#define EV_TRANSMITIR		0
#define T_TRANSMITIR		5

//Prototipos de funciones
void MensajesRX(void);
void TransmitirExpansion(void);
void EstadoInicial(void);
void Transmitir(void);
void BaseBoard (uint8_t c);
void Expansion1 (void);
void Expansion2 (uint8_t n);
void Expansion3 (uint8_t n);
void Expansion4 (void);

void Transmitir_TARJETA(void);
void Transmitir_TARJETA_INGRESO(void);

#endif /* AP_MENSAJES_H_ */
