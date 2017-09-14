/*
 * wav.h
 *
 *  Created on: 10 de set. de 2017
 *      Author: Gaston
 */

#ifndef WAV_H_
#define WAV_H_

#define INIC 0
#define REPRODUCCION 1
#define SENAL_INGRESO_CODIGO wav=0;reproduciendo=1;



extern __RW uint16_t wav;

extern __RW uint8_t reproduciendo;

unsigned long get_wav_size (int wav);


void reproducir_wav (int wav, char *reproduciendo);





#endif /* WAV_H_ */
