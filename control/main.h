/******************************************************************************
*
* Module: Control_ECU
*
* File Name: main.h
*
* Description: Header file for the AVR main driver
*
* Author: Mohamed Sarhan EL-hussieny
*
******************************************************************************/
#ifndef MAIN_H_
#define MAIN_H_

#include "external_eeprom.h"   // Include external EEPROM library
#include "gpio.h"              // Include GPIO library
#include "util/delay.h"        // Include delay library for _delay_ms() function
#include "twi.h"               // Include TWI/I2C library
#include "uart.h"              // Include UART library
#include "buzzer.h"            // Include buzzer library
#include "dcmotor.h"           // Include DC motor library
#include "timer.h"             // Include timer library
#include "std_types.h"         // Include standard types header file

// Function prototypes
uint8_t recive_pass(void);     // Function to receive and process passwords
uint8 check_match_pass(void);   // Function to check and execute operations based on received commands
void TIMER1_ticks(void);        // Function to handle TIMER1 ticks
void recieve_password_second(void); // Function to receive the second part of the password
void open_door_fun(void);       // Function to execute door opening operation
void sys_fail(void);            // Function to handle system failure

#endif /* MAIN_H_ */
