/*
 * funciones_fatfs.c
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */


#include "aplicacion.h"


typedef  unsigned char FIL;
typedef unsigned char FATFS;
#define FA_READ 0

int f_lseek (FIL *wav,unsigned int ofs);

void f_open (FIL *fp,char *path,unsigned int flag)
{return;}

int f_read (FIL *wav,uint32_t *buff,int btr,int *br);

void f_mount (FATFS *fp, char *path, unsigned int modo);

void f_close (FIL *fp);


int f_lseek (FIL *wav,unsigned int ofs)
{
	*((unsigned int *) wav)=ofs;
	return 0;
}



void f_mount (FATFS *fp, char *path, unsigned int modo)
{
	return;
}
void f_close (FIL *fp)
{
	return;
}
int f_read (FIL *fp,uint32_t *buff,int btr,int *br)
{
	unsigned int i;
	unsigned int j;
	unsigned int tam = ((unsigned int *) fp)[1];
	unsigned int pos = ((unsigned int *) fp)[0];

	if (pos==tam) return 0; //lei el archivo completo

	for (i=pos,j=0;i<pos+btr &&i< tam;i++,j++)
	{
		((uint8_t *)buff)[j]= fp[i];
	}
	*br=j;
	((unsigned int *) fp)[0]=i;
	return 0;
}



