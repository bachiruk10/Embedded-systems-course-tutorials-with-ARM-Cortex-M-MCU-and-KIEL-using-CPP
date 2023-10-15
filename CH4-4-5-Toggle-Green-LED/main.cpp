/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
// Program to blink 5 times Green LED 
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
