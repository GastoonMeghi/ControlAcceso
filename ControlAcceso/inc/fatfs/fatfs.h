/*
 * fatfs.h
 *
 *  Created on: Oct 14, 2017
 *      Author: Administrator
 */

#ifndef FATFS_H_
#define FATFS_H_
#include "ff.h"

FRESULT f_open (FIL* fp, const TCHAR* path, BYTE mode);				/* Open or create a file */
FRESULT f_close (FIL* fp);											/* Close an open file object */
FRESULT f_read (FIL* fp, void* buff, UINT btr, UINT* br);			/* Read data from the file */
FRESULT f_lseek (FIL* fp, FSIZE_t ofs);								/* Move file pointer of the file object */
FRESULT f_mount (FATFS* fs, const TCHAR* path, BYTE opt);			/* Mount/Unmount a logical drive */
TCHAR* f_gets (TCHAR* buff, int len, FIL* fp);						/* Get a string from the file */


#endif /* FATFS_H_ */
