/*
 * spi.h
 *
 *  Created on: Oct 26, 2016
 *      Author: Akshit
 */

#ifndef SOURCES_SPI_H_
#define SOURCES_SPI_H_

#include "MKL25Z4.h"
#include <stdint.h>

void spi_init(void);
uint8_t spi_write_read_byte(char spiMsg);
void spi_flush();

#endif /* SOURCES_SPI_H_ */
