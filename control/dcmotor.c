 /******************************************************************************
 *
 * Module: full DC-Motor Driver
 *
 * File Name:  dcmotor.c
 *
 * Description: DC-Motor Driver
 *
 * Author: Mohamed Sarhan AL-Hussieny
 *
 *******************************************************************************/

#include<avr/io.h>
#include"gpio.h"
#include"dcmotor.h"
#include"PWM.h"
void DcMotor_Init(void)
{


	GPIO_setupPinDirection(PORTA_ID, PIN0_ID, PIN_OUTPUT);    /* setup the direction for... */
	GPIO_setupPinDirection(PORTA_ID, PIN1_ID, PIN_OUTPUT);                             /*..... the two motor pins through the GPIO driver. */

    GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);      /*Stop at the DC-Motor at ...... */
    GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);                               /*....the beginning through the GPIO driver  */


}



void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	PWM_Timer0_Init(speed);                           //generate duty cycle
	switch(state){
	case MOTOR_OFF:
		GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
		break;
	case MOTOR_A_CW:
		GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_HIGH);
		break;
	case MOTOR_CW:
		GPIO_writePin(PORTA_ID, PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTA_ID, PIN1_ID, LOGIC_LOW);
		break;

	}




}
