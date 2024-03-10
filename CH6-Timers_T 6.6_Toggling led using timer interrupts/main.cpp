/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/************************************* Tutorial Tags *************************************
 Ticker class 
 Timout class
 attach(callback, time) member function to generate interrupts for Ticker and Timout classes
  GPIO Digital Input and outputs
*****************************************************************************************/

/* 6.4.2 Timer usage in C++ Language: *****************************************************

Tutorial 6-6: Toggling the green and red LEDs using timer interrupts, in C++ language  

In this tutorial we are toggling the red and green LEDs on the STM32F4 board. More precisely,
the green LED, connected to pin PG13 of the board, and red LED, connected to pin
PG14 of the board, will be toggled at 1 s intervals. There will be a 0.5 s delay
between the toggling operations in the red and green LEDs.
******************************************************************************************/

#include "mbed.h"

#define Delay 500 
// Digital output for illuminating leds 
DigitalOut Greenled(LED1);
DigitalOut Redled(LED2);
// Time_Delay to add a delay before starting ticker 2
Timeout Time_Delay;
// ticker1 to toggle periodically Greenled at 1s intervals
Ticker Ticker1;
// ticker2 to toggle periodically Redled at 1s intervals
Ticker Ticker2;

// Callback function for ticker interrupt
void toggleGreenled (){
    Greenled = !Greenled;
}

void toggleRedled (){
    Redled = !Redled;
}

// Callback function for Timeout interrupt
void Delayfunc () {
    toggleRedled ();
    Ticker2.attach(&toggleRedled, 1000ms);
}
    

int main()
{
    Time_Delay.attach(&Delayfunc, 500ms);
    Ticker1.attach(&toggleGreenled, 1000ms);

    while (true);
}
