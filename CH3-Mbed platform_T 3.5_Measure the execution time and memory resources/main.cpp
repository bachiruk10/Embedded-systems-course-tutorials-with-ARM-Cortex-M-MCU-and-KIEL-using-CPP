// Program to calculate program time execution and memory resources Stack and Heap

/*********************************** Tutorial Tags *********************************
Timers
Stack/ Heap memory usage
***********************************************************************************/

/* 3.4 Application: Tools for Analyzing the Generated Code: *************************
* Tutorial 3-5: Measuring the execution time and memory usage in Mbed Studio
*

In this tutorial, we use timers to measure execution time of a code block

We also execute functions to obtain data about memory reources consumed by code in heap 
stack memory

***************************************************************************/


// JSON file is added to program to display memory stats
#include "mbed.h"
#include <cstdint>
// Intialise variables for heap and stack and memory usage
mbed_stats_heap_t heapInfo;
mbed_stats_stack_t stackInfo;

uint32_t i;
uint32_t data[1000];


Timer myTimer;

// Define a led 
DigitalOut led1(LED1);

int main()
{
    // Time to meaure time of a foor loop
    myTimer.start();
    for(i=0; i<1000; i++){
        data[i] = i;
    }
    myTimer.stop();
    printf("Measurement execution time is %llu\n", myTimer.elapsed_time().count());
     
    // Timer to measure time of blinking a led
    uint64_t begin, end;

    myTimer.reset();
    myTimer.start();
    //begin = myTimer.elapsed_time().count();
    led1 = !led1;
    led1 = !led1;
    thread_sleep_for(3);
    myTimer.stop();
    end = myTimer.elapsed_time().count();
    printf("Time to blink a led is %llu\n", end);

    // get memory info 
    mbed_stats_heap_get(&heapInfo);
    printf("Heap size: %u\n", heapInfo.reserved_size);
    printf("Used heap: %u\n", heapInfo.current_size);

    mbed_stats_stack_get(&stackInfo);
    printf("Main stack size: %d\n", stackInfo.reserved_size);
    printf("Used main stack: %d\n", stackInfo.max_size);
        
    while (true)
    {
    }
}

