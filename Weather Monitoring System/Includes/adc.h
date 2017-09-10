/*
 * adc.h
 *
 *  Created on: Nov 27, 2016
 *      Author: Akshit
 */

#ifndef ADC_H_
#define ADC_H_


//This function initializes the ADC module
 void ADC0_init(void);

 //function to calibrate the ADC module
 int ADC0_calibrate(void);

 //function to calculate mean of samples
 int mean_filter(uint32_t result);

#endif /* ADC_H_ */
