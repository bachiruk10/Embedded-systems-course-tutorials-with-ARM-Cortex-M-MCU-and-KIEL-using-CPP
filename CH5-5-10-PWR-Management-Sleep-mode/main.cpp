/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn B(BUTTON1);

void getB(){
    led1 = !led1;
}



int main()
{
    led1 = 0;
    led2 = 0;
    B.fall(&getB);
    __enable_irq();
    

    while (true)
    {
        led2 = !led2;
        sleep();
    }
}
