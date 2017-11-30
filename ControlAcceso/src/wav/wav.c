/*
 * wav.c
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */
#include "aplicacion.h"
#include "ff.h"
#include "definiciones_wav.h"
__RW uint32_t cola_de_reproduccion[CANT_WAVS+5]; //le sumo 5 para no desbordar la cola

__RW long pos=-1; //posicion en cola de reproduccion, SE INICIALIZA EN "-1" por la manera en que se implemento reproducir wav, asi al introducir el primer elemento, toma la posicion 0

extern char SD[];


void inic_wav (void)
{
	static FATFS fs;
	FRESULT fr;

	fr=f_mount_SD(&fs, "", 1); //lo descomento para montar el disco
	bzero (cola_de_reproduccion,CANT_WAVS+5); //al inicializarlo en cero indico que la cola esta vacia
}


void reproducir_wav ( uint32_t wav)
{

	if (pos>CANT_WAVS+5) return; //seguridad, si supero el tamaño del array no hago nada

	cola_de_reproduccion[++pos]=wav; //pongo el wav en cola de reproduccion
}


void bzero (unsigned int *array,unsigned int tam)
{
	unsigned int i;

	for (i=0;i<tam;i++)
	{
		array[i]=0;
	}
}

int leer_buff_reproduccion (FIL *wav)
{
	static __RW uint16_t buff_reproduccion[TAM_BUFF_REPRODUCCION];
	static __RW uint32_t i; //variable que cuenta la cantidad de muestras de 16bits leidas
	static __RW uint32_t br; //cantidad de BYTES!!! leidos
	static __RW uint8_t estado=READ;


	if (estado==READ)
	{
		f_read_SD(wav,buff_reproduccion,TAM_BUFF_REPRODUCCION*sizeof (uint16_t),&br);
		i=0;
		if (br==TAM_BUFF_REPRODUCCION*sizeof (uint16_t))
			estado=NORMAL;
		else if (br==0)
			estado=TERMINE;
		else if (br<TAM_BUFF_REPRODUCCION*sizeof (uint16_t))
			estado=ULTIMO; //si leo menos bytes de los que deberia este es el fin del archivo
	}

	if (estado==NORMAL)
	{
		DACR&= ~(0x3FF<<6); //limpio los 10bits del DAC
		DACR|= ((0x3FF)& (   (buff_reproduccion[i++])/64)   )<<6; //divido por 64 para convertir de 16 a 10 bits
		if (i*sizeof(uint16_t)==br) //si ya lei todos los bytes del buff_reproduccion
		{
			estado=READ;
		}
	}

	if (estado==ULTIMO)
	{
		DACR&= ~(0x3FF<<6); //limpio los 10bits del DAC
		DACR|= ((0x3FF)& (   (buff_reproduccion[i++])/64)   )<<6; //divido por 64 para convertir de 16 a 10 bits
		//DACR|= ((0x3FF)& (   (buff_reproduccion[i++]))   )<<6; //adaptado a 8bits



		if (i*sizeof(uint16_t)==br)
		{
			estado=TERMINE;
		}
	}

	if (estado==TERMINE)
	{
		DACR&= ~(0x3FF<<6); //limpio los 10bits del DAC
		estado=READ;
		return 1;
	}
	return 0;

}








void WAV_TO_DAC (void)
{
	__RW uint32_t i;
	static __RW uint8_t estado=INIC;
	static FIL aux;
	FRESULT fr;

	if (estado==INIC) //abro el wav correspondiente
	{
		switch (cola_de_reproduccion[0])
		{
		case WAV_BIENVENIDO:
			fr=f_open_SD (&aux,"bienvenido.wav",FA_READ);
			break;
		case WAV_HASTA_LUEGO:
			f_open_SD (&aux,"hasta luego.wav",FA_READ);
			break;
		case WAV_CLAVE_INCORRECTA:
			f_open_SD (&aux,"codigo incorrecto.wav",FA_READ);
			break;
		case WAV_CLAVE_CORRECTA:
			f_open_SD (&aux,"codigo correcto.wav",FA_READ);
			break;
		case WAV_INGRESE_CODIGO:
			f_open_SD (&aux,"ingrese codigo.wav",FA_READ);
			break;
		case NO_WAV:
			return;
		//agregar un "else" para codigos no contemplados
		}
		f_lseek_SD (&aux,44); //lo posiciono para la lectura del archivo
		estado=REPRODUCCION;
	}

	if (estado==REPRODUCCION)
	{

		if (leer_buff_reproduccion (&aux)) //si termino el archivo
		{
			f_close_SD (&aux);
			estado = POP_COLA; //termine el archivo por lo tanto lo saco de la cola
		}

	}

	if (estado==POP_COLA)
	{
		for (i=0;i<pos;i++)
		cola_de_reproduccion[i]=cola_de_reproduccion[i+1]; //corro la cola hacia la "derecha" elminando el primer elemento


		cola_de_reproduccion[pos]=NO_WAV; //limpio el ultimo elememto de la cola
		pos--; //decremento la posicion del ultimo elemento
		estado =INIC;
	}

	if (estado==200) //aparecia 200 sin razon aparente, pruebo si esto lo arregla
	{
		estado=POP_COLA;
	}

}



