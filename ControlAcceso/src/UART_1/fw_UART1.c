#include "aplicacion.h"

void Inic_UART1 (void)
{
	PCONP |= 0x01<<4;					// Bit 4 en 1 prende la UART1:
	PCLKSEL0 &= ~(0x03<<8);				// Con un CCLK=100Mhz, nos queda PCLOCK=25Mhz
	U1LCR = 0x00000083;					// Transmision de 8 bits, 1 bit de stop, sin paridad, sin break cond, DLAB = 1:
	// 9600 baudios:
	U1DLM = 0;
	U1DLL = 0xA3;						// 0xA3 para 9600
	//setPINSEL(PORT0,15,PINSEL_FUNC1);	// TX1D P0[15]
	set_pinsel(PORT0,16,PINSEL_FUNC1);	// RX1D P0[16]
	U1LCR = 0x03;						// DLAB en 0:

	//Habilito las interrupciones
	U1IER = 0x03;
	ISER0 |= (1<<6);
}
