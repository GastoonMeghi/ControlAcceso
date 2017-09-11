/*
 * wav.c
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"
extern __RW unsigned int DAC_buff;

unsigned long get_wav_size (int wav)
{
	unsigned int aux;
	int br;
	f_lseek (wav,40);
	f_read (&aux,4,&br,wav);
	return aux;
}


void reproducir_wav (int wav, char *reproduciendo)
{
	static char estado=INIC;
	static unsigned long size;
	unsigned int aux,br;


	if (estado==INIC)
	{
		size=get_wav_size (wav);
		f_lseek (wav,44);
		estado=REPRODUCCION;
	}
	if (estado==REPRODUCCION)
	{
		f_read (&aux,4,&br,wav);
		DAC_buff= aux/64; //el dividir por 64 es para adaptar el maximo del archivo wav codificado en 16bit a el maximo del DAC condificado en 10bits 64 = numero_maximo_wav/numero_maximo_DAC
		size-=16; //cantidad de bits leidos

		if (size<16)
		{
			estado=INIC;
			size=0;
			*reproduciendo=0;
		}
	}
}
