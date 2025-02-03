/******************************************************************************
 *
 * Module: timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR timer driver
 *
 * Author: Mohamed Sarhan EL-hussieny
 *
 ******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "common_macros.h" // Include common macros header file
#include "std_types.h" // Include standard types header file

// Global variables for timer configuration
extern uint16 initial_value; // Initial value for the timer
extern uint16 compare_value; // Compare value for the timer (used in compare mode only)

// Enumeration for Timer1 mode
typedef enum
{
	Normal,ctc
}Timer1_Mode;

// Enumeration for Timer1 prescaler

typedef enum
{
	Noclock,Prescaler_1,Prescaler_8,Prescaler_64,Prescaler_256,Prescaler_1024
}Timer1_Prescaler;


// Configuration structure for Timer1
typedef struct {
    uint16 initial_value; // Initial value for the timer
    uint16 compare_value; // Compare value for the timer (used in compare mode only)
    Timer1_Prescaler prescaler; // Prescaler for Timer1
    Timer1_Mode mode; // Mode of operation for Timer1
} Timer1_ConfigType;

// Function prototypes
void Timer1_init(const Timer1_ConfigType *Config_Ptr); // Function to initialize Timer1
void Timer1_deInit(void); // Function to deinitialize Timer1
void Timer1_setCallBack(void (*a_ptr)(void)); // Function to set the callback for Timer1

#endif /* TIMER_H_ */



