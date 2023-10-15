/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

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