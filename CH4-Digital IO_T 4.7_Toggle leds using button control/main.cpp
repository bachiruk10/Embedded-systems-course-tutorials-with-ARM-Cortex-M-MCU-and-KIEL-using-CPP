/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */


/*********************************** Tutorial Tags *********************************
    GPIO output
    GPIO Input
    ***********************************************************************************/

/* 4.4.2 Digital IO usage in C++ Language: ****************************************************
* Tutorial 4-5: Turn on the green and red LEDs by specific button press count values, the C++ code
*

In this turotial, we have one counter. The counter is
used to turn on and off the green and red LEDs on the STM32F4 board via increasing
its value at each button press. When mod four of the counter has value zero, both
LEDs turn off. When mod four of the counter value has value one, only the red
LED turns on. When mod four of the counter value has value two, only the
green LED turns on. When mod four of the counter value has value three, both
LEDs turn on. 
*************************************************************************************/


#include "mbed.h"
#include <cstdint>
 
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalIn B(BUTTON1);


int main()
{
   
    uint32_t count = 0; 

    while (true)
    {
        if (B.read()==1){
        while (B == 1);
        count++;

        if(count%4==0){
            led1 = 0;
            led2 = 0;
        }
        else if (count%4==1){
            led1 = 0;
            led2 = 1;
        }
        else if (count%4==2){
            led1 = 1;
            led2 = 0;
        }
        else if (count%4==3){
            led1 = 1;
            led2 = 1;
        }
        }
        
    }
}
