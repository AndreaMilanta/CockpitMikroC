/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * List of Basic definitions for any PIC project
 */
 
#ifndef BASIC_H
#define BASIC_H
 
 //type definition
 typedef unsigned char uint8_t;
 typedef signed char int8_t ;
 typedef unsigned int uint16_t;
 typedef signed int int16_t;
 typedef unsigned long int uint32_t;
 typedef signed long int int32_t;
 
 // Standard Error definition
 #define ERROR -1

 // 1 and 0 equivalences
 #define TRUE 1
 #define FALSE 0
 #define HIGH 1
 #define LOW 0
 #define INPUT 1
 #define OUTPUT 0
 #define PULLUP 1
 #define PULLDOWN 0
 
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
 
 typedef struct 
 {
    uint8_t* port;
    uint8_t pos; 
 } pin;

 void setLow(pin p);
 void setHigh(pin p);
 uint8_t readPin(pin p);

#endif //BASIC_H