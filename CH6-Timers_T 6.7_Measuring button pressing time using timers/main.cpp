/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

	/***************************** Tutorial Tags ******************************
	 Timer class
     GPIO Digital output
     GPIO Interrupt
	 Serial monitor
	 **************************************************************************/

	/* 6.4.2 Timer Usage C++ Language: ******************************************
	* Tutorial 6-7: Measuring button pressing time using GPIO interrupts and timer,
	* in C++ language
	*

	In this tutorial we are turning on and off the green LED, connected to pin
	PG13 of the STM32F4 board. More precisely, the green LED will be turned on if
	pressing time of the user button, connected to pin PA0 of the STM32F4 board, is
	more than 3 s. If this time is less than 3 s, then the green LED turns off.

	We also try in this tutorial to use the printf() to print the processeing time 
    on the serial moonitor.

	***************************************************************************/

#include "mbed.h"
#include <chrono>
#include <stdio.h>

#define delay 3000

DigitalOut greenled(LED1);
InterruptIn PressButton(BUTTON1);
Timer timer1;
// Define variiable pressed time (time measured in milliseconds)
uint32_t PressedTime;


void TriggerRise() {
  timer1.start();
}

void TriggerFall() {
 
  PressedTime = chrono::duration_cast<chrono::milliseconds>(timer1.elapsed_time()).count();
  timer1.stop();
  // print the the pressed time on the serial monitor
  printf("Pressed time is : %u\r\n", PressedTime);

  if (PressedTime > delay) {
    greenled = 1;
  }
  else {
      greenled = 0;
  }
  timer1.reset();
}

int main() {
  // Generate GPIO interrupt on rising and falling edges of button press
  PressButton.rise(&TriggerRise);
  PressButton.fall(&TriggerFall);
  
  __enable_irq();
  while (true) {
  }
}
