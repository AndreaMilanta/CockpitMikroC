/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * List of Basic definitions for any PIC project
 */
 
#ifndef BASIC_H
#define BASIC_H
 
 // 1 and 0 equivalences
 #define TRUE 1
 #define FALSE 0
 #define HIGH 1
 #define LOW 0
 #define T TRUE
 #define F FALSE
 #define INPUT 1
 #define OUTPUT 0
 
 // Edge
 #define RISING_EDGE 0
 #define FALLING_EDGE 1
 
 // Numeric Constants
 #define MAX_TIMER_PERIOD_VALUE 65535
 
 // Priorities
 //#define REAL_TIME_PRIORITY 0
 #define DISABLED 0           // according to datasheet priority 0 equals disabling the interrupt
 #define HIGHEST_PRIORITY 1
 #define VERY_HIGH_PRIORITY 2
 #define HIGH_PRIORITY 3
 #define MEDIUM_PRIORITY 4
 #define LOW_PRIORITY 5
 #define VERY_LOW_PRIORITY 6
 #define LOWEST_PRIORITY 7
 
#endif //BASIC_H