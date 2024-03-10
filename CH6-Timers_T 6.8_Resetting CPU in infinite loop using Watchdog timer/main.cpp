/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

	/***************************** Tutorial Tags ******************************
	 Independent Watchdog (IWDG)Timer
     Ticker class (timers)
	 GPIO Digital output
	 GPIO Interrupt
	 **************************************************************************/

	/*  6.4.2 Timer Usage C++ Language: ******************************************
	* Tutorial 6-8: Using the watchdog timer to reset stuck system, in C++ language
	*

    Use the IWDG to reset the CPU when the code goes into an infinite loop

	So, the watchdog timer is started with 4000 ms timeout value. The watchdog is 
    reset and the green LED is toggled every second. When the user presses the 
    onboard button, the system is stuck in an infinite loop. The green LED stops 
    toggling. After 4 s, the system is reset by the watchdog timer. 
    Hence, the green LED starts toggling again.
	***************************************************************************/

#include "mbed.h"

// Define global variables
InterruptIn Button(BUTTON1);
DigitalOut greenled(LED1);
Ticker ticker;

// Define watchdog class instance
Watchdog &watchdog = Watchdog::get_instance();

void TriggerInfloop();
void Toggleled();


int main()
{
    // Define timeout value
    uint32_t timeout = 5000; // milliseconds

    // Start the watchdog
    watchdog.start(timeout);
    
    // Timer to periodically toggle the green led every second
    ticker.attach(&Toggleled, 1s);
    
    // enable interrupt
    Button.rise(&TriggerInfloop);
    __enable_irq();

    while (true);
}

// Callback functions
void Toggleled(){
    greenled = !greenled;
    // Refresh the watchdog timer
    watchdog.kick();
}

void TriggerInfloop(){
    while(true);
}


