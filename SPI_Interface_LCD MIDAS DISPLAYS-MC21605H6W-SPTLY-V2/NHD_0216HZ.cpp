/*----------------------------------------------------------------------------
 Newhaven NHD0216HZ LCD C/C++ file
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "NHD_0216HZ.h"
#include <cstdint>


#define SPI__MOSI D11
#define SPI__SCLK D13
#define SPI__CS PB_0

DigitalOut SS(SPI__CS);     //slave select a.k.a. cs or latch for shift reg
SPI spi(SPI__MOSI, NC, SPI__SCLK);

//Initialise SPI
void init_spi(void) {
    SS = 1;
    
    spi.format(8, 0);         //8bit spi mode 2
    spi.frequency(100000);    //100 kHz spi clock
}

//Initialise LCD
void init_lcd(void) {
    printf("Start of program\r\n");
    wait_us(40000);

    SS = 0;
    // write_cmd(0x01);
    spi.write(0x30);
    SS = 1;
    write_cmd(0x01); // Clear display  b0001
    wait_us(1520);
    wait_us(37);
    write_cmd(0x20);
    wait_us(37);
    write_cmd(0x20); //
    wait_us(37);
    write_cmd(0x0C); // Display ON or OPF  b1100
    wait_us(37);
    write_cmd(0x01); // Clear display  b0001
    wait_us(1520);
    write_cmd(0x06); // Entry mode b0110
    wait_us(37);
    write_cmd(0x28); // Function set 4bit/ 2lines
    wait_us(37);
    //write_cmd(0x01);
    //wait_us(1520);

}

//Write 4bits to the LCD
void write_4bit(int nibble, int mode) {
    SS = 0;
    uint8_t data = nibble | ENABLE | mode;
    //printf("1st w %u\r\n", data);
    spi.write(data);
    SS = 1;
    wait_us(1);
    SS = 0;
    data = nibble & ~ENABLE;
    // printf("2nd w %u\r\n", data);
    spi.write(data);
    SS = 1;
}

//Write a command to the LCD
void write_cmd(int data) {
    int hi_n;
    int lo_n;
    
    hi_n = (data & 0xF0);

    lo_n = ((data << 4) &0xF0);
    
/*     SS = 0;
    uint8_t d = hi_n | ENABLE | COMMAND_MODE;
    //printf("1st w %u\r\n", data);
    spi.write(d);
    SS = 1;
    wait_us(1);
    SS = 0;
    d = hi_n & ~ENABLE;
    // printf("2nd w %u\r\n", data);
    spi.write(d);
    SS = 1;


    SS = 0;
    d = lo_n | ENABLE | COMMAND_MODE;
    //printf("1st w %u\r\n", data);
    spi.write(d);
    SS = 1;
    wait_us(1);
    SS = 0;
    d = lo_n & ~ENABLE;
    // printf("2nd w %u\r\n", data);
    spi.write(d);
    SS = 1; */

    //printf("1st w %u, %u\r\n", d, d2);

    write_4bit(hi_n, COMMAND_MODE);
    write_4bit(lo_n, COMMAND_MODE);
}

//Write data to the LCD
void write_data(char c) {
    int hi_n;
    int lo_n;
    
    hi_n = (c & 0xF0);
    lo_n = ((c << 4) &0xF0);
    
    write_4bit(hi_n, DATA_MODE);
    write_4bit(lo_n, DATA_MODE);
}

//Set cursor position
void set_cursor(int column, int row) {
    int addr;
    
    addr = (row * LINE_LENGTH) + column;
    addr |= TOT_LENGTH;
    write_cmd(addr);
}

//Print strings to the LCD
void print_lcd(const char *string) {
    while(*string){
        write_data(*string++);
    }
}

// *******************************ARM University Program Copyright (c) ARM Ltd 2019*************************************
