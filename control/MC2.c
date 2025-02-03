/******************************************************************************
*
* Module: Control_ECU
*
* File Name: MC2.c
*
* Description: Source file for the AVR MC2 driver
*
* Author: Mohamed Sarhan EL-hussieny
*
*******************************************************************************/

#include "external_eeprom.h" // Include external EEPROM library
#include "gpio.h"            // Include GPIO library
#include "util/delay.h"      // Include delay library for _delay_ms() function
#include "twi.h"             // Include TWI/I2C library
#include "uart.h"            // Include UART library
#include "buzzer.h"          // Include buzzer library
#include "main.h"            // Include main header file
#include "dcmotor.h"         // Include DC motor library
#include "timer.h"           // Include timer library
#include <avr/io.h>          // Include AVR I/O definitions

// Define commands and states
#define CHANGE_PASSWORD   '-'       // Command to change password
#define OPEN_DOOR         '+'       // Command to open door
#define CREATE_PASSWORD   'a'       // Command to create password
#define ERRORP_PASSWORD   0x50      // Command to report password error
#define NOT_OPEN          'u'       // State indicating door is not open
#define DONT_CHANGE       'D'       // Flag indicating no change in password

uint8 recive_op = 0, order;

int main()
{
    // Initialize TWI/I2C
    TWI_ConfigType Config2 = {10, baud_rate16}; // Define TWI configuration structure
    TWI_init(&Config2);                          // Initialize TWI with the specified configuration

    // Initialize DC motor
    DcMotor_Init(); // Initialize DC motor

    // Initialize buzzer
    Buzzer_init();

    // Initialize UART
    UART_ConfigType Config = {eight_bit, Even_parity, one_bit, baud_rate9600}; // Define UART configuration structure
    UART_init(&Config);                                                        // Initialize UART with the specified configuration

    // Enable global interrupts
    SREG |= (1 << 7); // Set the global interrupt enable bit

    // Initialize Timer1
    Timer1_ConfigType timer1 = {0, 31250, Prescaler_256, ctc}; // Define Timer1 configuration
    Timer1_init(&timer1);                                       // Initialize Timer1 with the specified configuration
    Timer1_setCallBack(TIMER1_ticks);                            // Set the callback function for Timer1

    // Main loop
    while (1)
    {
        // Receive operation from UART
        recive_op = UART_recieveByte();

        // Switch based on received operation
        switch (recive_op)
        {
        case CREATE_PASSWORD:
            recive_pass(); // Receive and process password from UART
            break;

        case OPEN_DOOR:
            order = check_match_pass(); // Check for matching password and execute operations
            UART_sendByte(order);
            if (order == 1)
            {
                open_door_fun();          // Function to execute door opening operation
            }
            break;

        case ERRORP_PASSWORD:
            sys_fail();     // Function to handle system failure

            break;

        case CHANGE_PASSWORD:
            order = check_match_pass();
            UART_sendByte(order);
            break;
        }
    }
}
