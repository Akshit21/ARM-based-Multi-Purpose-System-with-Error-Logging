/*
 * log.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Akshit
 */

#ifndef INCLUDES_LOG_H_
#define INCLUDES_LOG_H_

#include<stdint.h>
void LOG_0(uint8_t * data);	//log function with no parameters
void LOG_1(uint8_t * data,uint32_t param);	//log function with 2 parameters Integer Number and data type
void LOG_2(uint8_t * data,float param);		//log function with 2 paramets Floating number and size of float

void my_ftoa(float data, char *str, int number_after_decimal);		// Function to create a floating number to String which is passed to log2
int my_itoa(char *str, int data, int d);							// Function to create a integer number to String which is passed to log1
void reverse(char *str, int len);
uint8_t myAtoi(uint8_t *str);
void converthex(char *data, unsigned int a);



#endif /* INCLUDES_LOG_H_ */
