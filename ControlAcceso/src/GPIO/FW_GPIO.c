#include "aplicacion.h"

void set_pinsel( uint8_t port , uint8_t pin ,uint8_t sel)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINSEL[ port ] = PINSEL[ port ] & ( ~ ( 3 << pin ) );
	PINSEL[ port ] = PINSEL[ port ] | ( sel << pin );
}

void set_pinmode( uint8_t port , uint8_t pin ,uint8_t modo)
{
	port = port * 2 + pin / 16;
	pin = ( pin % 16 ) * 2;
	PINMODE[ port ] = PINMODE[ port ] & ( ~ ( 3 << pin ) );
	PINMODE[ port ] = PINMODE[ port ] | ( modo << pin );
}

void set_dir( uint8_t port , uint8_t pin , uint8_t dir )
{
	port = port * 8;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( dir << pin );
}

void set_pin( uint8_t port , uint8_t pin , uint8_t estado )
{
	port = port * 8 + 5;

	GPIOs[ port ] = GPIOs[ port ] & ( ~ ( 1 << pin ) );
	GPIOs[ port ] = GPIOs[ port ] | ( estado << pin );
}

uint8_t get_pin( uint8_t port , uint8_t pin , uint8_t actividad )
{
	port = port * 8 + 5;

	return ( ( ( GPIOs[ port ] >> pin ) & 1 ) == actividad ) ? 1 : 0;

}

void toggle_pin( uint8_t port , uint8_t pin)
{
	port = port * 8 + 5;

	if ( (GPIOs[ port ] >> pin) & 1 )
		GPIOs[ port ] &= ( ~ ( 1 << pin ) );
	else
		GPIOs[ port ] |= ( 1 << pin );
}

void set_pinmodeOD ( uint8_t port, uint8_t bit,  uint8_t modo)
{
	PINMODE_OD[port] &= ~(0x01<<bit);
	PINMODE_OD[port] |= (modo<<bit);
}
