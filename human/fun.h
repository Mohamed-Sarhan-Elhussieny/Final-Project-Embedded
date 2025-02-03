/******************************************************************************
*
* Module: FUN
*
* File Name: FUN.h
*
* Description: Header file for the AVR FUN driver
*
* Author: Mohamed Sarhan EL-hussieny
*
******************************************************************************/

#ifndef FUN_H_
#define FUN_H_

#include "std_types.h"   // Include standard data types header file
#include <util/delay.h>  // Include delay functions header file
#include "keypad.h"      // Include keypad driver header file
#include "lcd.h"         // Include LCD driver header file
#include "uart.h"        // Include UART driver header file
#include <avr/io.h>      // Include AVR I/O header file (for SREG register)
#include "timer.h"       // Include timer driver header file

#define SIZE_OF_PASS 5   // Define size of password

// Function prototypes

/*
* Function: getpass_frist_fun
* ----------------------------
* Initializes the process of getting the first part of the password from the user.
* Prompts the user to enter the password and sends it to the CONTROL_ECU.
*/
void getpass_frist_fun(void);

/*
* Function: get_pass
* -------------------
* Gets the password from the user via keypad.
* Stores the entered password in the provided array pointer.
*/
void get_pass(uint8 *ptr);

/*
* Function: check_pass_in_all_case
* --------------------------------
* Handles the process of checking the password entered by the user.
* Prompts the user to enter the password and sends it to the CONTROL_ECU for verification.
*/
void check_pass_in_all_case(void);

/*
* Function: sendPasswordFunction
* -------------------------------
* Sends the password to the CONTROL_ECU.
* Accepts an array pointer containing the password to be sent.
*/
void sendPasswordFunction(uint8 *ptr);


/*
* Function: BUZZER
* -----------------
* Activates the buzzer in case of an error.
* Sends a command to the CONTROL_ECU to enable the buzzer.
*/
void BUZZER(void);

#endif /* FUN_H_ */
