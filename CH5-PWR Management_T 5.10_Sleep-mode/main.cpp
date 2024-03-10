/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*********************** Tutorial Tags *********************** 
 GPIO Digital Input and outputs
 GPIO Interrupts
 Power management modes: Sleep mode
**************************************************************/

/* 5.6.2 Power Modes in C++ Language: Tutorial 5-10************* 
The recent Mbed release only has one function sleep() related to sleep modes and
power management operations. Therefore, there is not much we can do to adjust the
power modes manually. Instead, we should depend on the sleep() function for this
operation. We direct the reader to the Mbed web site for further information on this
topic.
We provide a sample code on the usage of the sleep() function.
This code works as follows. Device settings for the red and green LEDs on the
STM32F4 board are done first. Then, interrupt settings for the user button are done.
The green LED toggles within the callback function. The red LED toggles within the
infinite loop under the main function. The sleep() function is also in the infinite
loop. Therefore, in the first run, the red LED toggles and CPU goes to sleep waiting
for a GPIO interrupt. As the user presses the button on the STM32F4 board, the CPU
wakes up and toggles the green LED. Afterward, the CPU goes to thread mode and
toggles the red LED and sleeps again. This example shows how the sleep mode can
be used under Mbed in its basic sense.
**************************************************************/



#include "mbed.h"

DigitalOut green_led(LED1);
DigitalOut red_led(LED2);
InterruptIn UserButtton(BUTTON1);

// Callback function to execute when receiving an interrupt
void CallbackFunc(){
    green_led = !green_led;
}

int main()
{
    // Initialise states of red and green leds
    green_led = 0;
    red_led = 0;
    // Generate an interrupts on falling edge of User Button GPIO
    UserButtton.fall(&CallbackFunc);
    // Enable interrupts
    __enable_irq();

    while (true)
    {
        red_led = !red_led;
        // CPU enter sleep mode using sleep()
        sleep();
    }
}
