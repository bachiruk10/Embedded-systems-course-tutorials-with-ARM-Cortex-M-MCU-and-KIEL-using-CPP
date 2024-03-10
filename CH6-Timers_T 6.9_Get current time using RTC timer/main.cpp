/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
/*********************************** Tutorial Tags *********************************
Real Time Clock (RTC) Timer
GPIO Interrupt
UART - printf
***********************************************************************************/

/* 6.4.1 Timer Usage C Language: ****************************************************
* Tutorial 6-5: Using the alarm property of RTC, in C language
*

In this tutorial, we use the RTC to observe the current time when the user button 
is pressed

We first set the date as “31 July 2020 18:18:18.”
When the user button is pressed, the current time based on the set date is displayed

***************************************************************************/
#include "mbed.h"
#include <cstdint>

// Global private variables
tm date;
uint32_t flag = 0;

InterruptIn Button(BUTTON1);

// Callback func

void getcurrentTime();

int main() {
  // H:M:S
  date.tm_hour = 0;
  date.tm_min = 0;
  date.tm_sec = 0;
  // D:M:Y
  date.tm_mday = 1;
  date.tm_mon = 0;
  date.tm_year = 123; // tm_year calculated from 1900

  /** Set the current time
  time_t mktime(tm *date) returns the time as the number of seconds lapsed from Jan 1, 1970
  set_time(time_t t) uses the returned value from mktime() to set the time to the desired date a
  and time
  */

  set_time(mktime(&date));

  __enable_irq();
  Button.rise(&getcurrentTime);

  while (true) {
    if (flag == 1) {
      time_t seconds = time(NULL);
      // ctime(time_t *timer) returns the current time in www Mmm dd hh:mm:ss yyyy
      // time_t timer is in seconds and can be obtained from RTC by time(NULL) 
      printf("Current Time = %s\r\n", ctime(&seconds));
      flag = 0;
    }
  }
}
// Callback function
void getcurrentTime() { flag = 1; }

