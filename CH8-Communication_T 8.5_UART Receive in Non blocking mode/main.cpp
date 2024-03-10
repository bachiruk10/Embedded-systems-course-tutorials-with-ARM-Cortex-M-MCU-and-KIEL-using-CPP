/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
/***************************** Tutorial Tags ******************************
    	 UART receive mode only
		 UART with interrupts
		 GPIO Digital outputs
    **************************************************************************/

/* 8.2.4 UART Usage in the STM32F4Microcontroller: *************************
* Tutorial 8-5: Usage of the UART/USART module in non blocking operation mode,
* the C++ code

    In this tutorial, we configure stm32 to receive characters through UART from PC
    Build project , so when when the character ’g’ is received,
    the green LED connected to pin PG13 of the STM32F4 board is toggled. When
    the character ’r’ is received, the red LED connected to pin PG14 of the STM32F4
    board is toggled.

    As the project is compiled and run, the code will wait to receive data from
    the UART module. To test the code, send the characters ’r’ and ’g’ from the
    host PC to the STM32F4 microcontroller. Hence, we can observe that the red
    and green LEDs toggle.
***************************************************************************/
#include "mbed.h"
#include <cstdio>
#include <stdio.h>

#define BAUDRATE 115200 

DigitalOut greenled(LED1);
DigitalOut redled(LED2);

// Note: USBTX and USBRX is UART1 connected to PC via STLink
UnbufferedSerial serialPort (USBTX, USBRX);

// Storage for one character
char char_buf;


// Callback function for serial Rx interrupt


void UARTRx_ISR(){
    // read serial port USBRX
    serialPort.read(&char_buf, 1);
    // Conditions for GPIO control
    if (char_buf == 'g'){
        greenled = !greenled;
    }
    else if (char_buf == 'r'){
        redled = !redled;
    }
    else {
        greenled = 0;
        redled = 0;
    }
}

int main()
{
    serialPort.baud(BAUDRATE);
    serialPort.format(8, SerialBase::None, 1);
    
    serialPort.attach(&UARTRx_ISR, SerialBase::RxIrq);
    
    while (true);
}


