 /******************************************************************************
 *
 * Module: dc motor
 *
 * File Name: dc motor.h
 *
 * Description: header file for  dc motor driver
 *
 * Author: Mohamed Sarhan AL-Hussieny
 *
 *******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
#include "std_types.h"
#include "PWM.h"


typedef enum
{
	MOTOR_OFF,MOTOR_CW,MOTOR_A_CW
}DcMotor_State;

/*
 >>Description
➢ The Function responsible for setup the direction for the two
motor pins through the GPIO driver.
➢ Stop at the DC-Motor at the beginning through the GPIO driver.
 */

void DcMotor_Init(void);

/*
>> Description:
➢ The function responsible for rotate the DC Motor CW/ or A-CW or
stop the motor based on the state input state value.
➢ Send the required duty cycle to the PWM driver based on the
required speed value.
 */
void DcMotor_Rotate(DcMotor_State,uint8 speed);


#endif /* DCMOTOR_H_ */
