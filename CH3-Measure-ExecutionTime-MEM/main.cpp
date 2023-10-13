#include "mbed.h"

#define WAIT_TIME_MS 5000 
DigitalOut led1(LED1);

int main()
{
    printf("This is the unning on Mbed OS\n");


    while (true)
    {
        led1 = 0;
        thread_sleep_for(WAIT_TIME_MS);
    }
}

