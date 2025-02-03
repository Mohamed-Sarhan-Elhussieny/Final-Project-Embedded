/******************************************************************************
*
* Module: FUN
*
* File Name: FUN.c
*
* Description: Source file for the AVR FUN driver
*
* Author: Mohamed Sarhan EL-hussieny
*
******************************************************************************/

#include "fun.h"

// Define commands for changing and reporting errors with passwords
#define CHANGE_PASSWORD 0x40
#define ERRORP_PASSWORD 0x50
#define SIZE_OF_PASS 5

// Arrays to store passwords
uint8 arr_to_store_pass1[SIZE_OF_PASS]={0};
uint8 arr_to_store_pass2[SIZE_OF_PASS]={0};
uint8 arr_to_store_pass3[SIZE_OF_PASS]={0};
uint8 i;

// Function to get password from user via keypad
void get_pass(uint8 *ptr)
{
    uint8 key,i;
    for (i = 0; i < 5; i++)
    {
        // Get the pressed key number, if any switch pressed for more than 500 ms it will
        // be considered more than one press
        key = KEYPAD_getPressedKey();
        if ((key <= 9) && (key >= 0))
        {
            ptr[i]=key;      // Send the pressed key to the CONTROL_ECU
            LCD_displayCharacter('*'); // Display the pressed keypad switch
            _delay_ms(250);
        }
        else
        {
            i--; // To make the UART send five numbers only not including any characters
        }
    }
}

// Function to get first password from user
void getpass_frist_fun(void)
{
    LCD_clearScreen();
    // Prompt the user to enter the password
    LCD_displayString("Plz Enter Pass:");
    LCD_moveCursor(1, 0);
    uint8 key;

    get_pass(arr_to_store_pass1); // Get the first password

    // Wait until '=' is pressed to indicate the end of password input
    while(KEYPAD_getPressedKey()!= '=');

    LCD_clearScreen();
    LCD_displayString("enter pass again:");
    LCD_moveCursor(1, 0);

    get_pass(arr_to_store_pass2); // Get the second password

    // Wait until '=' is pressed to indicate the end of password input
    while(KEYPAD_getPressedKey()!= '=');

    // Send both passwords over UART
    sendPasswordFunction(arr_to_store_pass1);
    sendPasswordFunction(arr_to_store_pass2);
}

// Function to send password over UART
void sendPasswordFunction (uint8 *ptr)
{
    for( i=0 ; i < 5 ; i++)
    {
        UART_sendByte(ptr[i]); // Send each digit of the password
    }
}

// Function to check entered password against stored passwords
void check_pass_in_all_case(void)
{
    LCD_clearScreen();
    LCD_displayString("Enter pass");
    LCD_moveCursor(1,0);
    uint8 key;
    for (i = 0; i < 5; i++)
    {
        // Get the pressed key number, if any switch pressed for more than 500 ms it will
        // be considered more than one press
        key = KEYPAD_getPressedKey();
        if ((key <= 9) && (key >= 0))
        {
            arr_to_store_pass3[i]=key; // Store the pressed key
            LCD_displayCharacter('*'); // Display '*' to indicate a pressed key
            _delay_ms(250);
        }
        else
        {
            continue;
        }
        _delay_ms(250);
    }

    // Wait until '=' is pressed to indicate the end of password input
    while(KEYPAD_getPressedKey()!='=');

    // Send the entered password over UART
    sendPasswordFunction(arr_to_store_pass3);
}
