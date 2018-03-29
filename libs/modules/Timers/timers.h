/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * Library to simply timers setups and handling
 */

#ifndef TIMERS_H
#define TIMERS_H

 #include "basic.h"
 #include "current.h"

 #ifdef TIMER1_DEVICE
     // Faster timer operations
     #define clearTimer1() TIMER1_OCCURRED = FALSE
     // Interrupt handler
     #define onTimer1Interrupt void timer1_interrupt() iv IVT_ADDR_T1INTERRUPT ics ICS_AUTO
 #endif //TIMER1_DEVICE

 #ifdef TIMER2_DEVICE
     // Faster timer operations
     #define clearTimer2() TIMER2_OCCURRED = FALSE
     // Interrupt handler
     #define onTimer2Interrupt void timer2_interrupt() iv IVT_ADDR_T2INTERRUPT ics ICS_AUTO
 #endif //TIMER2_DEVICE

 #ifdef TIMER4_DEVICE
     // Faster timer operations
     #define clearTimer4() TIMER4_OCCURRED = FALSE
     #define turnOnTimer4() TIMER4_ENABLE = TRUE
     #define turnOffTimer4() TIMER4_ENABLE = FALSE
     // Interrupt handler
     #define onTimer4Interrupt void timer4_interrupt() iv IVT_ADDR_T4INTERRUPT ics ICS_AUTO
 #endif //TIMER4_DEVICE
 

//public function
 void setTimer(uint8_t device, double timePeriod);

 void setTimerInterruptPriority(uint8_t device, uint8_t priority);
 
 void startTimer(uint8_t device);
 
 void stopTimer(uint8_t device);
 
 void turnOffTimer(uint8_t device);

//private functions
 uint16_t _getTimerPeriod(double timePeriod, uint8_t prescalerIndex);
 
 uint16_t _getTimerPrescaler(double timePeriod);

#endif //TIMERS_H