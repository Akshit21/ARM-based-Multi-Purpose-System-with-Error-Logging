/*
 * I2C.c
 *
 *  Created on: Nov 19, 2016
 *      Author: Akshit
 */

/*
 * This file contains I2c protocol functions
 * Initialization, Read and Write to I2C data register
 * It uses 2 lines
 * SCL:Clock line
 * SDA:Data line
 *
 * It is synchronous serial communication protocol.
 */
#include "MKL25Z4.h"
#include "I2C.h"

//Function to initialize I2C communication
void I2C_init(void)
{
	//I2C0 module initialization
		SIM_SCGC4 |= SIM_SCGC4_I2C0_MASK;		// Turn on clock to I2C0 module
		SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;		// Turn on clock to Port E module
		PORTE_PCR0 = PORT_PCR_MUX(5);			// PTE0 pin is I2C0 SCL line
		PORTE_PCR1 = PORT_PCR_MUX(5);			// PTE1 pin is I2C0 SDA line
		I2C0_F  = 0x14; 						// SDA hold time = 2.125us, SCL start hold time = 4.25us, SCL stop hold time = 5.125us *
		I2C0_C1 = I2C_C1_IICEN_MASK;    		// Enable I2C0 module
}

/*
 * Function to write on I2C register
 * Parameters: 	Slave Address: Which device we want to write
 * 			  	Register Address: Which register we want to write
 * 			  	Data: Data we want to write
 */
void I2C_WriteRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, /*unsigned*/ char u8Data)
{
	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C0_D = u8Data;												/* Send the data */
	I2C_Wait();

	I2C_Stop();

    Pause(50);
}

/*
 * Function to read a byte from I2C register
 * Parameters: 	Slave Address: Which device we want to read
 * 			  	Register Address: Which register we want to read
 *
 */
unsigned char I2C_ReadRegister(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress)
{
	unsigned char result;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();

	I2C_EnterRxMode();
	I2C_DisableAck();

	result = I2C0_D;
	I2C_Wait();
	I2C_Stop();
	result = I2C0_D;
	Pause(50);
	return result;
}

/*
 * Function to read multiple byte from I2C register
 * Parameters: 	Slave Address: Which device we want to read
 * 			  	Register Address: Which register we want to read
 * 			  	length: No of bytes to be read
 *				Array pointer: to store the data in array
 */
void I2C_ReadMultiRegisters(unsigned char u8SlaveAddress, unsigned char u8RegisterAddress, unsigned char n, unsigned char *r)
{
	char i;

	I2C_Start();
	I2C0_D = u8SlaveAddress << 1;									/* Send I2C device address with W/R bit = 0 */
	I2C_Wait();

	I2C0_D = u8RegisterAddress;										/* Send register address */
	I2C_Wait();

	I2C_RepeatedStart();

	I2C0_D = (u8SlaveAddress << 1) | 0x01;							/* Send I2C device address this time with W/R bit = 1 */
	I2C_Wait();

	I2C_EnterRxMode();
	I2C_EnableAck();

	i = I2C0_D;
	I2C_Wait();

	for(i=0; i<n-2; i++)
	{
	    *r = I2C0_D;
	    r++;
	    I2C_Wait();
	}

	I2C_DisableAck();
	*r = I2C0_D;
	r++;
	I2C_Wait();
	I2C_Stop();
	*r = I2C0_D;
	Pause(50);
}

//Delay function
void Pause(int number)
{
	int cnt;
	for(cnt=0; cnt<number; cnt++)
	{
		__asm("nop");
	};
}
