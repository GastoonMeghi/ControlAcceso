/*
 * fatfs.h
 *
 *  Created on: 17 de set. de 2017
 *      Author: Gaston
 */

#ifndef FATFS_FATFS_H_
#define FATFS_FATFS_H_

#include "aplicacion.h"
#include "GPIO.h"
typedef  unsigned char FIL;
typedef unsigned char FATFS;
#define FA_READ 0

int f_lseek (FIL *wav,unsigned int ofs);

void f_open (FIL *fp,char *path,unsigned int flag);

int f_read (FIL *wav,uint32_t *buff,int btr,int *br);

void f_mount (FATFS *fp, char *path, unsigned int modo);

void f_close (FIL *fp);

#endif /* FATFS_FATFS_H_ */
