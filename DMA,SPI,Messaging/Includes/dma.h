/*
 * dma.h
 *
 *  Created on: Oct 31, 2016
 *      Author: Aagam
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

void memmove_dma8(uint8_t * src, uint8_t * dst, uint32_t length);
void memmove_dma32(uint32_t * src, uint32_t * dst, uint32_t length);

#endif /* INCLUDES_DMA_H_ */
