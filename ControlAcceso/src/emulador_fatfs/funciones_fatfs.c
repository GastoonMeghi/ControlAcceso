/*
 * funciones_fatfs.c
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */


#include "aplicacion.h"

extern char SD[];

volatile unsigned long pos=0;

int f_lseek (int wav,unsigned int ofs)
{
	pos=ofs;
	return 0;
}


int f_read (unsigned int *buff,int btr,int *br,int wav)
{
	unsigned int i;
	unsigned char aux[4];

	for (i=0;i<btr;i++)
	{
		aux[i]=SD[pos+i];
	}
	pos+=i;
	*br=i;
	*buff= *((unsigned int *)aux);
	return 0;
}
