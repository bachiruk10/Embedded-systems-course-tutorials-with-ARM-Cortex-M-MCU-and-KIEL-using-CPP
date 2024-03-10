/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
/***************************** Tutorial Tags ******************************
        UART Transmit only
        GPIO Digital outputs
    **************************************************************************/

/* 8.2.4 UART Usage in the STM32F4Microcontroller: *************************
    * Tutorial 8-4: Usage of the UART/USART module in blocking operation mode,
    * the C++ code

    In this tutorial, we send a a string and counter value to PC from the STM32F4
    microcontroller via ST-LINK virtual COM port every 2 s. The green LED connected
    to pin PG13 of the STM32F4 board is toggled once data is transmitted. In this
    example, the UART module is configured in blocking mode. On the PC side, we
    can use an application such as RealTerm
    ***************************************************************************/
#include "mbed.h"
#include <cstdio>
#include <stdio.h>

#define WAIT_TIME_MS 2000
#define BAUDRATE 115200 

DigitalOut greenled(LED1);
BufferedSerial serialPort (USBTX, USBRX);

uint8_t mymessage[] = "Hello from STM32F4 Discovery!\r\n";
char cnt_buf[10];
uint16_t counter;

int main()
{
    serialPort.set_baud(BAUDRATE);
    
    while (true)
    {
        sprintf(cnt_buf, "%d\r\n", counter++);
        // Send string
        serialPort.write(mymessage, sizeof(mymessage));
        // Send counter
        serialPort.write(cnt_buf, sizeof(cnt_buf));
        // toggle led
        greenled = !greenled;
        thread_sleep_for(WAIT_TIME_MS);
    }
}
