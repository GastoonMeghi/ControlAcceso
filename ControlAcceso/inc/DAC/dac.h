/*
 * dac.h
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */

#ifndef DAC_DAC_H_
#define DAC_DAC_H_

#define DACR *((unsigned int *) 0x4008C000)
#define AOUT 2
#define P026 0,26

void inic_dac (void);

void escribir_dac (int dato);

#endif /* DAC_DAC_H_ */
