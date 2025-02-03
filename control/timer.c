/******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR timer driver
 *
 * Author: Mohamed Sarhan EL-hussieny
 *
 *******************************************************************************/
#include <avr/io.h>
#include <avr/interrupt.h>
#include"timer.h"

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/* global variable contain the ticks count of the timer */
//unsigned char g_tick = 0;

/* Interrupt Service Routine for timer1 compare mode */
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{

		(*g_callBackPtr)(); /*  call the function g_callBackPtr(); */
	}
}

/* Interrupt Service Routine for timer1 compare mode */

ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{

		(*g_callBackPtr)(); /*  call the function g_callBackPtr(); */
	}
}




void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{

	TCNT1 = Config_Ptr->initial_value; 	/* Set timer1 initial count  */

	OCR1A = Config_Ptr->compare_value;   /* Set the Compare value*/


	   /* Configure timer control register TCCR1A
		 * 1. Timer1_ Mode
		 * 2. Prescaler
		 */

	TCCR1A |=  (1<<FOC1A)  ;

	TCCR1B |= (Config_Ptr->mode << WGM12) ;

	TCCR1B |= (Config_Ptr->prescaler);

	TIMSK |= (1<<TOIE1); /* Enable Timer1 Compare A Interrupt */


	TIMSK=(1<<OCIE1A);  /* Enable Timer1 Compare A Interrupt */

}





void Timer1_deInit(void)
{
/*********************************  Stop Timer1 **********************************************************/


	TCCR1B=0;
	TCCR1A = 0;
	/*
  TCCR1B &= ~(1<<CS10);
  TCCR1B &= ~(1<<CS11);       //  No clock source (Timer/Counter stopped).
  TCCR1B &= ~(1<<CS12);
 */
  }


 void Timer1_setCallBack(void(*a_ptr)(void))
 {
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}
