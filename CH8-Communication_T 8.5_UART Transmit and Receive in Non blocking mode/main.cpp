/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
	/***************************** Tutorial Tags ******************************
		 UART Transmit and Receive
		 UART with interrupts
		 GPIO Digital outputs
		 GPIO Interrupts
		 Memory allocation and printf() on console serial terminal
	 **************************************************************************/

	/* 8.2.4 UART Usage in the STM32F4Microcontroller: ************************************************************
	 * Tutorial 8-2: Usage of the UART/USART module in non-blocking loopback operation mode, the
	C++ code

	 In this tutorial, we configure UART5 on STM32 board to trasnmit and receive its own sent data
	 To do so, connect Tx and Rx of UART5 together using a jumper. and build code with UART5 configured
	 as Trnasnmit and Receive. When the user button is pressed a string message is sent from Tx,
	 and green led is toggled. Then, when the message is recived, the red led is toggled.
	 Make use of interrupts for implementation

	 To expand this tutorial, allocate memory for the buffer intended to receive the data using pointers,
	 and check whether memory allocation has been successful. Print on STM32 serial terminal whether allocation was successful

	 ****************************************************************************************************************/
#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <stdio.h>

InterruptIn button (BUTTON1);
DigitalOut greenled(LED1);
DigitalOut redled(LED2);


// UART 5 is used here. Pin names correspond to the STM32F4 Discovery board, refer to board data sheet
UnbufferedSerial serialPort (PC_12, PD_2, 9600); 

// String message 
uint8_t serTxData [] = "Hello from Tx pin!";
uint8_t *serRxData;


void UARTTx_ISR();
void UARTRx_ISR();


// Callback function for Digital Input interrupt
void trigger_UART(){

    serialPort.attach(&UARTTx_ISR, SerialBase::TxIrq);

}

void UARTTx_ISR(){
    //  Transmit string message
    serialPort.write(serTxData, sizeof(serTxData));
    // Toggle green led when transmit successful
    greenled = 1;
    serialPort.attach(&UARTRx_ISR, SerialBase::RxIrq);

}

void UARTRx_ISR(){
    // read serial port UART5 from STM32 board
    serialPort.read(serRxData, sizeof(serRxData));
    
    //thread_sleep_for(2000); // milliseconds

    // Conditions for GPIO control

    if (serRxData[0] == serTxData[0]){
        redled = 1;
		printf("Data received successfully!\r\n");
	}
	if (!strcmp ((char*)serRxData,(char*)serTxData)){
        redled = 1;
		printf("Data received successfully!\r\n");
	}
}

int main()
{
    // Reset state for leds 
    greenled = 0; redled = 0;
    // Set format for UART frame
    serialPort.format(8, SerialBase::None, 1);
    // Gnerate interrupt on signal rising edge
    button.rise(&trigger_UART);

    __enable_irq();

    // Allocate storga for receive buffer 
    serRxData = new uint8_t [100];

    if(serRxData == NULL){
        printf("Failure to allocate memory!\r\n");
    }
    else
    {
        printf("Memory allocated successfully!\r\n");
    }
    
    while (true);
    
}


