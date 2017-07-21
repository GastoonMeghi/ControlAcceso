/*
 * GPIO.h
 *
 *  Created on: 1 de jun. de 2017
 *      Author: Gaston
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


	typedef 	unsigned int 	uint32_t;
	typedef 	unsigned short 	uint16_t;
	typedef 	unsigned char 	uint8_t;

	//////////////FIRMWARE GPIO/////////////
    void set_pinsel( uint8_t port , uint8_t pin ,uint8_t sel);

    void set_pinmode( uint8_t port , uint8_t pin ,uint8_t modo);

    void set_pinmodeOD ( uint8_t port, uint8_t bit,  uint8_t modo);

    void set_dir( uint8_t port , uint8_t pin , uint8_t dir );

    void set_pin( uint8_t port , uint8_t pin , uint8_t estado );

    uint8_t get_pin( uint8_t port , uint8_t pin , uint8_t actividad );

    void toggle_pin( uint8_t port , uint8_t pin);

	/////////////////INICILIZACION GPIO////////////////////////


    //void inic_GPIO (void);













    //!< ----------- Estados de PINSEL:

	#define		PINSEL_GPIO			0
	#define		PINSEL_FUNC1		1
	#define		PINSEL_FUNC2		2
	#define		PINSEL_FUNC3		3

    #define		ACTIVO_BAJO		0
    #define		ACTIVO_ALTO		1

	// dirección en FIODIR
	#define 	ENTRADA			0
	#define 	SALIDA			1

	// identificadores de los puertos
	#define 	PORT0			0
	#define 	PORT1			1
	#define 	PORT2			2
	#define 	PORT3			3
	#define 	PORT4			4

    //modos de entrada
	#define PULL_UP 0
	//modos de salida
	#define OPEN_DRAIN 0

#endif /* GPIO_GPIO_H_ */
