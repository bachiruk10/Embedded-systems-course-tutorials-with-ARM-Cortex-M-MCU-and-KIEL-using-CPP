/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
	/***************************** Tutorial Tags ******************************
		 SPI Full duplex
		 GPIO Digital outputs
	 **************************************************************************/

	/* 8.3.4 SPI Usage in the STM32F4Microcontroller: *************************
	 * Tutorial 8-12: Usage of the SPI module in blocking operation mode, the C++ code

	Make a project to send data from SPI4 to SPI5 set as master and slave respectively.
	There are two counter values in the
	code. The first one will be sent to the slave from master. Upon receiving this data
	by the slave, the green LED connected to pin PG13 of the STM32F4 board will
	toggle if mod 3 of the received counter value is equal to zero. Afterward, the second
	counter will be sent to master from slave. Upon receiving this data by the master,
	the red LED connected to pin PG14 of the STM32F4 board will toggle if mod 5 of
	the received counter value is equal to zero. This operation will repeat every 2 s.
	***************************************************************************/
#include "mbed.h"
#include <cstdint>

#define WAIT_TIME_MS 2000 
DigitalOut greenled(LED1);
DigitalOut redled(LED2);
// SPI4 as Master
SPI Master (PE_6, PE_5, PE_2, PE_4);
// SPI5 as Slave
SPISlave Slave(PF_9, PF_8, PF_7, PF_6);

// Data to be sent by master and slave
uint8_t masterTxdata = 0, slaveTxdata = 0;

// Buffer for receive data by master and slave
uint8_t masterRxdata, slaveRxdata;

int main()
{
    // Baud rate 100 k bits/sec
    int freq = 100e3; 
    // Frame width 
    int bits = 8;
    // Sample mode 
    int mode = 0;
    Master.frequency(freq);
    Master.format(bits, mode);
    Slave.frequency(freq);
    Slave.format(bits, mode);
    
     slaveTxdata++;
    //printf("This is the bare metal blinky example running on Mbed OS %d.%d.%d.\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);

    while (true)
    {
        masterTxdata++;
	   
        Master.select();

        masterRxdata = Master.write(masterTxdata);

        if(Slave.receive()){
            slaveRxdata = Slave.read();
            slaveTxdata++;
            Slave.reply(slaveTxdata);
        } 

        Master.deselect();
        if(masterRxdata %5 ==0)
        greenled = !greenled;

	    if(slaveRxdata %3 ==0)
        redled = !redled;

        thread_sleep_for(WAIT_TIME_MS);
        
    }
}
