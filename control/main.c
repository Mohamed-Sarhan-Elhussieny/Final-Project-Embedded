/******************************************************************************
 *
 * Module: main
 *
 * File Name: main.c
 *
 * Description: Source file for the AVR main driver
 *
 * Author: Mohamed Sarhan EL-hussieny
 *
 ******************************************************************************/

#include "main.h"               // Include main header file
#include <util/delay.h>         // Include delay functions

#define SIZE_OF_PASS 5          // Define size of password
#define CHANGE_PASSWORD   '-'   // Command to change password
#define OPEN_DOOR      '+'      // Command to open door
#define CREATE_PASSWORD   'a'   // Command to create password

/*******************************************************************************
 * Variable (Private) *
 ******************************************************************************/
uint8 address = 0;              // EEPROM address
uint8 g_tick = 0;               // Global tick counter

unsigned char i = 0;            // Loop counter
uint8 arrary_to_store_pass1[SIZE_OF_PASS]; // Array to store first received password
uint8 arrary_to_store_pass2[SIZE_OF_PASS]; // Array to store second received password
uint8 arrary_to_check_pass[SIZE_OF_PASS];
uint8 check_correct_of_pass = 1; // Flag to check if passwords match

/*******************************************************************************
 * Function to receive and validate passwords from UART *
 ******************************************************************************/
// Receiving and validating passwords
uint8_t recive_pass(void)
{
    // Receiving the first password
    for(i = 0; i < SIZE_OF_PASS; i++)
    {
        arrary_to_store_pass1[i] = UART_recieveByte();
    }

    // Receiving the second password
    for(i = 0; i < SIZE_OF_PASS; i++)
    {
        arrary_to_store_pass2[i] = UART_recieveByte();
    }

    // Comparing the two passwords and writing to EEPROM if they match
    for(i = 0; i < SIZE_OF_PASS; i++)
    {
        if(arrary_to_store_pass1[i] != arrary_to_store_pass2[i])
        {
            check_correct_of_pass = 0; // Passwords do not match
        }
    }
    if(check_correct_of_pass)
    {
        for(i = 0; i < SIZE_OF_PASS; i++)
        {
            // Writing passwords to EEPROM
            EEPROM_writeByte(((address) + i), arrary_to_store_pass1[i]);
            _delay_ms(10);
        }
    }
    UART_sendByte(check_correct_of_pass); // Send status of password matching
    check_correct_of_pass = 1; // Reset the flag
}

// Function to handle system failure
void sys_fail(void)
{
    g_tick = 0;
    Buzzer_on(); // Turn on the buzzer
    while(g_tick <= 60); // Wait for a certain duration
    Buzzer_off(); // Turn off the buzzer
}

// Function to check and execute operations based on received commands
uint8 check_match_pass(void)
{
    // Command to execute when receiving '74'
    check_correct_of_pass = 1;
    for(i = 0; i < SIZE_OF_PASS; i++)
    {
        arrary_to_check_pass[i] = UART_recieveByte();
    }
    for(i = 0; i < SIZE_OF_PASS; i++)
    {
        EEPROM_readByte(((address) + i), &arrary_to_store_pass1[i]);
        _delay_ms(10);

        if(arrary_to_store_pass1[i] != arrary_to_check_pass[i])
        {
            check_correct_of_pass = 0; // Passwords do not match
        }
    }
    return check_correct_of_pass;
}

// Function to execute door opening operation
void open_door_fun(void)
{
    // Command to execute when receiving '19'
    g_tick = 0;
    DcMotor_Rotate(MOTOR_CW, 100); // Rotate the DC motor clockwise
    while(g_tick != 15); // Wait for a certain duration
    DcMotor_Rotate(MOTOR_OFF, 0); // Turn off the DC motor
    while(g_tick != 18); // Wait for a certain duration
    DcMotor_Rotate(MOTOR_A_CW, 100); // Rotate the DC motor clockwise
    while(g_tick != 33);
    DcMotor_Rotate(MOTOR_OFF, 0);
}

// Function to handle TIMER1 ticks
void TIMER1_ticks(void)
{
    g_tick++; // Increment the tick counter
}
