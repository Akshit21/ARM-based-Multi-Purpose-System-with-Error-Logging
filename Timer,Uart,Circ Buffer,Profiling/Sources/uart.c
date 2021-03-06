/******************************************** Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved *
* The information contained herein is property of the Authors. The copying and distribution of the files is prohibited except by express written agreement with the Authors. * 
* Authors: Akshit Shah and Aagam Shah Date Edited: 10 October 2016 * ********************************************************/

/*
 * This file contains three functions
 *  uart_init -> UART Configuration
 * RGB_init -> RGB Configuration
 * UART_IRQHandler -> Interrupt processing
 */

/*This function is for UART Configuration*/
#include "main.h"

void uart_init(uint32_t baud_rate)
{

	// STEP1:Clock Configuration //
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;		//Selecting Port A
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
    SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);  	//Selecting clock source for UART0 as MCGFLLCLK


	//STEP2: GPIO Port Configuration //
	PORTA_PCR1 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for UART0_Rx
	PORTA_PCR2 |= PORT_PCR_MUX(2);			//Select Alternate function 2 for UART0_Tx


	//STEP3: Disable TX and RX bits //
	UART0_C2 &= ~(UART0_C2_TE_MASK|UART0_C2_RE_MASK);


	//STEP4: Configuring Desired Settings //
	UART0_BDH &= ~UART_BDH_SBNS_MASK;		// Select 1 stop bit
	// Select 8 BIT FRAME,No Parity,Loop mode
	UART0_C1  &= ~(UART_C1_M_MASK|UART_C1_PE_MASK|UART0_C1_LOOPS_MASK);


	//STEP5: SETTING BAUD RATE //
	uint32_t sbr_val,osr_val=16,reg_temp;
	sbr_val=(uint32_t)(SystemCoreClock/(baud_rate*osr_val));
	reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));
	UART0_BDH = reg_temp | UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
	UART0_BDL = (uint8_t)(sbr_val & UART0_BDL_SBR_MASK);


	 //STEP6: Enabling interrupts //
	 // Transmit Interrupt Enable for TDRE// Receive Interrupt Enable for RDRF // Enable TX and RX bits //
	 UART0_C2 |= UART0_C2_TIE_MASK|UART0_C2_RIE_MASK|UART0_C2_TE_MASK|UART0_C2_RE_MASK;
	 NVIC_EnableIRQ(UART0_IRQn); //The function enables a device-specific interrupt in the NVIC interrupt controller.
	 __enable_irq();	//  This function enables IRQ interrupts by clearing the I-bit in the CPSR
}

/*This function is for RGB_LED configuration*/

void RGB_init(void)
{
    SIM_SCGC6 |= SIM_SCGC6_TPM2_MASK|SIM_SCGC6_TPM0_MASK;	// Enable TPM2 for Red and Green, TPM0 for Blue
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);						// Select MCGFLLCLK

    TPM2_SC =0;
    TPM0_SC =0;			//Disable Clock
    TPM2_MOD = 20970;
    TPM0_MOD = 20970;	//Set Counter

    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK; 	//Enable Port B and Port D
    PORTB_PCR18 |= PORT_PCR_MUX(3);	// Select Alt 3
    PORTB_PCR19 |= PORT_PCR_MUX(3);	// Select Alt 3
    PORTD_PCR1  |= PORT_PCR_MUX(4);	// Select Alt 4

    PTB_BASE_PTR->PDDR = 1 << 18;	// Enable Port B pin 18 (Red) as output
    PTB_BASE_PTR->PDDR = 1 << 19;	// Enable Port B pin 19 (Green) as output
    PTD_BASE_PTR->PDDR = 1 << 1;  	// Enable Port D pin 1 (Blue) as output

    TPM2_C0SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; // Select Edge-aligned PWM
    TPM2_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
    TPM0_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;

    TPM2_SC |= TPM_SC_CMOD(1) | TPM_SC_PS(0);	// Enable Clock Counter
    TPM0_SC |= TPM_SC_CMOD(1) | TPM_SC_PS(0);
}

//This function is Interrupt Handler
uint8_t read_data;
int length=0,i;
int data=0;
void UART0_IRQHandler (void)
{
  if (UART0_S1&UART_S1_RDRF_MASK)
	  	{
	  	  read_data=UART0_D;
	  	//UART0_C2 &= ~UART0_C2_RIE_MASK; 		//Peripheral interrupt disable (RX)
#ifdef RGB_TEST
//for controlling LED through interrupts
	 	if((read_data=='a'))
	  		{
	  			next_colour++;
	  			LOG_0("\r\nNEXT COLOUR\r\n",15);
	  		}
	  	if((read_data=='d'))
	  		{
	  			if (next_colour==1)
	  				next_colour=9;
	  			next_colour--;
	  			LOG_0("\r\nPREVIOUS COLOUR\r\n",19);
	  		}
	  	if( (read_data=='w') & (B<1))
	  		{
	  			B=B+0.1;
	  			LOG_0("\r\nBRIGHTNESS HIGH\r\n",19);
	  		}
	  	if((read_data=='s') & (B>0) )
	  		{
	  			B=B-0.1;
	  			LOG_0("\r\nBRIGHTNESS LOW\r\n",18);
	  		}
	  	UART0_C2 |=  UART0_C2_TIE_MASK;
#endif
#ifdef BUFFER
	 	Add_Item(&RXBUFF,read_data);				//Add Items in the receiving buffer
	    length++;				// Length of Input string
	    if(length==Max)
	  		{
	    		data++;
	    		LOG_0("\r\nReceive buffer full\r\n",23);
	    		length=0;
	  		}
#endif
	  	}
  	  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
  	  {
  		  UART0_D = read_data;
#ifdef BUFFER
  		  if(data==0)
  			  UART0_D = read_data;
  		  if(data==2)							//transmit when data is copied from rxbuff to txbuff
  			  {
  			 	  i=0;
  			 	  while(i<Max)
  			 	  {
  			 		  read_data = Remove_Item(&TXBUFF);			//output from tx buff
  			 		  while(!((UART0_S1&UART_S1_TDRE_MASK)|(UART0_S1&UART_S1_TC_MASK)));
  			 		  UART0_D = read_data;
  			 		  i++;
  			 	  }
  				  if(BufEmpty(&TXBUFF))
  				  {
  					  UART0_C2 &= ~UART0_C2_TIE_MASK; 	//Disable Interrupt Enable for TDRE if buffer is empty
  					  data=3;
  				  }
  			  }
#endif
  		UART0_C2 &= ~UART_C2_TIE_MASK;
  		UART0_C2 |= UART0_C2_RIE_MASK;
  	  }
}
