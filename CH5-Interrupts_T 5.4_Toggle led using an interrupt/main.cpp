/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*********************************** Tutorial Tags *********************************
    GPIO output
    GPIO Interrupt
    ***********************************************************************************/

/* 5.3.2 interrupt usage in C++ Language: ****************************************************
* Tutorial 5-4: Toggle the onboard green LED using an interrupt, the C++ code
*

Build project to generate an interrpt when a button is pressed. The interrupt is used
to toggle the onboard green led on stm32f4 board. 
*************************************************************************************/
#include "mbed.h"

InterruptIn userButton(BUTTON1);
DigitalOut led1(LED1);

// callback function
void getButtons(){
    led1 = !led1;
}

int main() {
    led1 = 0;

    userButton.rise(&getButtons);
    __enable_irq();

  while (true);
}
