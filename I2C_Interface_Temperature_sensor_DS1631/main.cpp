/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdint>

# define UART_TX D1
# define UART_RX D0
# define I2C_SCL D15
# define I2C_SDA D14





//I2C interface
I2C temp_sensor(I2C_SDA, I2C_SCL);
//Serial pc(UART_TX, UART_RX);

//I2C address of temperature sensor DS1631
const int temp_addr = 0x90;

char commands[] = {0x51, 0xAA, 0xAC};
char read_temp[2];
char read_config[1], write_config = 0xD;
int counter;


/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){

    char cmd_ctr[2] = {commands[2],  write_config};
    printf("Temp = %x \r\n", cmd_ctr[1]);
    
    //Write 0x51 to 0x90 to start temperature conversion
    temp_sensor.write(temp_addr, cmd_ctr, 2, false);


    temp_sensor.write(temp_addr, &commands[2], 1, false);
    temp_sensor.read(temp_addr, read_config, 1);

    printf("Temp = %x \r\n", *read_config);
  


	while(1){
        
		//Write 0x51 to 0x90 to start temperature conversion
		temp_sensor.write(temp_addr, &commands[0], 1, false);
		
		ThisThread::sleep_for(2000ms);
		
		//Write 0xAA to 0x90 to read the last converted temperature
		temp_sensor.write(temp_addr, &commands[1], 1, false);
		//Read the temperature into the read_temp array
		temp_sensor.read(temp_addr, read_temp, 2);
		
		//Convert temperature to Celsius
		float temp = (float((read_temp[0] << 8) | read_temp[1]) / 256);

        // Access and read the config reg
        if (counter == 0){
             temp_sensor.write(temp_addr, &commands[2], 1, false);

            temp_sensor.read(temp_addr, read_config, 1);


            printf("Temp = %x \r\n", *read_config);
        }
        counter++;
        
       

		
		//Print temperature to the serial monitor
		//printf("Temp = %.2f \r\n", temp);
	}
}
