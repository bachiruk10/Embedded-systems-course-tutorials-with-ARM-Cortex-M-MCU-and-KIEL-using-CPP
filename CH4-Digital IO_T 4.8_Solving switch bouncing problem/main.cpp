/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*********************** Tutorial Tags *********************** 
 GPIO Digital Input and outputs
 Counter
 Switch Debouncing
**************************************************************/

/* 4.4.2 Digital IO usage in C++ Language: ****************************************************
* Tutorial 4-8: Turn on the green and red LEDs by specific button press count values with switch
bouncing handled, the C++ code
*

The tutorial re implements the code in tutorial 4.7. Additionally, we use an additional shift register to
eliminate switch bouncing in this code.
*************************************************************************************/

#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalIn B(BUTTON1);


int main()
{
   
    uint32_t Mask = 0x7fff; 
    uint32_t count = 0, reg = 0;
     

    while (true)
    {
        reg = (reg << 1) +  B.read(); 

        if (reg == Mask){
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

