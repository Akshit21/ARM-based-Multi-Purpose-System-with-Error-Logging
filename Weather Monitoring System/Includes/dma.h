/*
 * dma.h
 *
 *  Created on: Dec 7, 2016
 *      Author: Akshit
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_
#include "MKL25Z4.h"

//#define DMA_PROFILE_TEST
#define SIZE8
//#define SIZE32
#define MEMMOVE
//#define MEMZERO

void memmove_dma8(uint8_t * src, uint8_t * dst, uint32_t length);
void memmove_dma32(uint32_t * src, uint32_t * dst, uint32_t length);


#endif /* INCLUDES_DMA_H_ */
