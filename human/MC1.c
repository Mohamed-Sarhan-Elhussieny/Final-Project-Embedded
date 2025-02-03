/******************************************************************************
*
* Module: HMI_ECU
*
* File Name: mc1.c
*
* Description: Source file for the AVR HMI_ECU driver
*
* Author: Mohamed Sarhan EL-hussieny
*
******************************************************************************/

#include "keypad.h"     // Include keypad library
#include "lcd.h"        // Include LCD library
#include "uart.h"       // Include UART library
#include <avr/io.h>     // Include AVR I/O definitions
#include <util/delay.h> // Include delay functions
#include "timer.h"      // Include timer library
#include "fun.h"        // Include custom functions and variables declarations

// Define commands and states
#define CHANGE_PASSWORD   '-'       // Command to change password
#define OPEN_DOOR         '+'       // Command to open door
#define CREATE_PASSWORD   'a'       // Command to create password
#define NOT_OPEN          'u'       // State indicating door is not open
#define DONT_CHANGE       'D'       // Flag indicating no change in password
#define ERRORP_PASSWORD   0x50      // Command to report password error

// Global variables
uint8 check_correct_of_pass = 1;     // Flag to check correct password
uint8 wrong_try = 0;                 // Counter for wrong attempts
uint8 user_choice = NOT_OPEN;        // User's choice
unsigned char g_tick = 0;            // Global tick counter

uint8 creat_pass_state = 1;          // State for creating password
uint8 flagPassword, pass_state;

// Timer callback function
void TIMER1_ticks(void)
{
    g_tick++;
}

int main(void)
{
    // Initialize Timer1
    Timer1_ConfigType timer1 = {0, 31250, Prescaler_256, ctc}; // Define Timer1 configuration
    Timer1_init(&timer1);                                       // Initialize Timer1 with specified configuration
    Timer1_setCallBack(TIMER1_ticks);                            // Set callback function for Timer1

    // Enable global interrupts
    SREG |= (1 << 7); // Set the global interrupt enable bit

    // Initialize UART
    UART_ConfigType Config = {eight_bit, Even_parity, one_bit, baud_rate9600}; // Define UART configuration
    UART_init(&Config);                                                        // Initialize UART with specified configuration

    // Initialize LCD
    LCD_init(); // Initialize LCD display

    // Main loop
    while (1)
    {
        // Password Creation State
        while (creat_pass_state == 1)
        {
            UART_sendByte(CREATE_PASSWORD); // Send command to create password
            getpass_frist_fun();            // Function to get the first part of the password
            pass_state = UART_recieveByte(); // Receive pass state

            if (pass_state == 1)
            {
                creat_pass_state = 0; // Exit password creation state
            }
            else
            {
                // Inform user about unmatched password
                LCD_clearScreen();
                LCD_displayString("unmatched pass");
                _delay_ms(1000);
                wrong_try++;
                LCD_clearScreen();
                LCD_displayString("Try again.");
                _delay_ms(1000);
                creat_pass_state = 1; // Continue password creation state
                break;
            }
        }

        // User Choice State
        if (!wrong_try)
        {
            LCD_clearScreen();
            LCD_displayString("+ : Open Door");
            LCD_moveCursor(1, 0);
            LCD_displayString("- : Change Password");
            user_choice = KEYPAD_getPressedKey();
        }

        // Open Door State
        while (wrong_try < 3 && user_choice == OPEN_DOOR)
        {
            if (user_choice == OPEN_DOOR)
            {
                UART_sendByte(OPEN_DOOR); // Send command to open door
                LCD_clearScreen();        // Clear LCD
                _delay_ms(300);
                check_pass_in_all_case(); // Function to check password
                _delay_ms(100);

                flagPassword = UART_recieveByte(); // Receive checking of password
                if (flagPassword == 1)            // Flag is set when password matches
                {
                    // Door unlocking process
                    LCD_clearScreen();
                    LCD_displayString("Door is Unlocking");
                    g_tick = 0;
                    while (g_tick != 18); // Wait for a certain duration
                    LCD_clearScreen();
                    LCD_displayString("Door is Locking");
                    while (g_tick != 33); // Wait for a certain duration

                    flagPassword = 0; // Reset flag
                    wrong_try = 0;    // Reset tries
                    break;
                }
                else
                {
                    wrong_try++; // Increment tries
                }
            }
        }

        // Change Password State
        while (wrong_try < 3 && user_choice == CHANGE_PASSWORD)
        {
            if (user_choice == CHANGE_PASSWORD)
            {
                UART_sendByte(CHANGE_PASSWORD); // Send command to change password
                LCD_clearScreen();              // Clear LCD
                _delay_ms(300);
                check_pass_in_all_case(); // Function to check password
                _delay_ms(200);

                flagPassword = UART_recieveByte(); // Receive checking of password
                if (flagPassword == 1)            // Flag is set when password matches
                {
                    creat_pass_state = 1; // Reset flag
                    wrong_try = 0;        // Reset tries
                    break;
                }
                else
                {
                    wrong_try++; // Increment tries
                }
            }
        }

        // Handling wrong attempts
        if (wrong_try == 3)
        {
            g_tick = 0;
            LCD_clearScreen();
            LCD_displayString("Wrong Try");
            LCD_moveCursor(1, 0);
            LCD_displayString("ERROR!!!!");
            UART_sendByte(ERRORP_PASSWORD); // Command to make CONTROL_ECU ready
            while (g_tick <= 60);           // Wait for a certain duration
            wrong_try = 0;
        }
    }
}
