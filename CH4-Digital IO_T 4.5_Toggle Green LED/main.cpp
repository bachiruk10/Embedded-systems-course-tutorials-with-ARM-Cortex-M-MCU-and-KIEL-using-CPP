/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*********************************** Tutorial Tags *********************************
    GPIO output
    ***********************************************************************************/

/* 4.4.2 Digital IO usage in C++ Language: ****************************************************
* Tutorial 4-5: Toggle the onboard green LED by delay functions, the C++ code
*

In this turotial, we uses the HAL library functions to toggle the green LED (connected 
to pin PG13) on the STM32F4 board for 5 times using a delay function
Use printf() to print a counter value everytime the led is toggled

*************************************************************************************/
#include "mbed.h"


// Blinking rate in milliseconds
#define Delay     1s


int main()
{
    int i = 1;

    #ifndef Mask
    #define Mask i << 13
    #else
    #define Mask 0
    #endif

    PortOut Gled (PortG, Mask);
    int c = 0;

    while (true) {

      while(c < 5) {
        Gled = Mask;
        ThisThread::sleep_for(Delay);
        Gled = 0;
        ThisThread::sleep_for(Delay);
        c++;
        printf("value of c %d\n", c);
      }
    }
}

