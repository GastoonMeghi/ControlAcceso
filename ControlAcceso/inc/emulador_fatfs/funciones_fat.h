/*
 * funciones_fat.h
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */

#ifndef EMULADOR_FATFS_FUNCIONES_FAT_H_
#define EMULADOR_FATFS_FUNCIONES_FAT_H_



int f_lseek (int wav,unsigned int ofs);


int f_read (unsigned int *buff,int btr,int *br,int wav);

#endif /* EMULADOR_FATFS_FUNCIONES_FAT_H_ */
