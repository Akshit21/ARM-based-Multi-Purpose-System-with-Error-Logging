/*
 * uart.h
 *
 *  Created on: Nov 28, 2016
 *      Author: Akshit
 */

#ifndef INCLUDES_UART_H_
#define INCLUDES_UART_H_
#include <stdint.h>

void uart_init(uint32_t baud);
void UART0_IRQHandler (void);
void RGB_init(void);
void UART0_WriteString(char string[]);
void UART0_WriteChar(char BYTE);
void UART0_ReadString(char string[]);

char UART0_ReadChar();

#define R(bright) TPM2_C0V=TPM2_MOD *(bright)		// Red led control with Brightness 'B'
#define G(bright) TPM2_C1V=TPM2_MOD *(bright)		// Green led control with Brightness 'B'
#define B(bright) TPM0_C1V=TPM0_MOD *(bright)		// Blue led control with Brightness 'B'

#define R_ON	TPM2_C0V = TPM2_MOD
#define R_OFF	TPM2_C0V = 0

#define G_ON	TPM2_C1V = TPM2_MOD
#define G_OFF	TPM2_C1V = 0

#define B_ON	TPM0_C1V = TPM0_MOD
#define B_OFF	TPM0_C1V = 0

#define baud 38400			//baud rate



#endif /* INCLUDES_UART_H_ */
