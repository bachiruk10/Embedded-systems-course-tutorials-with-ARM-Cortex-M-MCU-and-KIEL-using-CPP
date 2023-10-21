/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

InterruptIn userButton(BUTTON1);
DigitalOut led1(LED1);

void getButtons(){
    led1 = !led1;
}

int main() {
    led1 = 0;
    userButton.rise(&getButtons);
    __enable_irq();

  while (true);
}
