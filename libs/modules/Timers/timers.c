/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * Library to simply timers setups and handling
 */

#include "timers.h"
void setTimer(uint8_t device, double timePeriod) 
{
    unsigned char prescalerIndex;
    setTimerInterruptPriority(device, MEDIUM_PRIORITY);
    //TimePeriod = TimerPeriod * TimerPrescaler * InstructionPeriod
    prescalerIndex = _getTimerPrescaler(timePeriod);
    switch (device) 
    {
        #ifdef TIMER1_DEVICE    
            case TIMER1_DEVICE:
                TIMER1_PERIOD = _getTimerPeriod(timePeriod, prescalerIndex);
                TIMER1_ENABLE_INTERRUPT = TRUE;
                T1CON = 0x8004;
                //TIMER1_ENABLE = TRUE;
                //TIMER1_PRESCALER = prescalerIndex;
                break;
        #endif  //TIMER1_DEVICE

        #ifdef TIMER2_DEVICE    
            case TIMER2_DEVICE:
                TIMER2_PERIOD = _getTimerPeriod(timePeriod, prescalerIndex);
                TIMER2_ENABLE_INTERRUPT = TRUE;
                TIMER2_ENABLE = TRUE;
                TIMER2_PRESCALER = prescalerIndex;
                break;
        #endif  //TIMER2_DEVICE

        #ifdef TIMER4_DEVICE    
            case TIMER4_DEVICE:
                TIMER4_PERIOD = _getTimerPeriod(timePeriod, prescalerIndex);
                TIMER4_ENABLE_INTERRUPT = TRUE;
                TIMER4_ENABLE = TRUE;
                TIMER4_PRESCALER = prescalerIndex;
                break;
        #endif  //TIMER4_DEVICE
    }
}


void setTimerInterruptPriority(uint8_t device, uint8_t priority) 
{
    switch (device) 
    {
        #ifdef TIMER1_DEVICE    
            case TIMER1_DEVICE:
                TIMER1_PRIORITY = priority;
                break;
        #endif  //TIMER1_DEVICE

        #ifdef TIMER2_DEVICE    
            case TIMER2_DEVICE:
                TIMER2_PRIORITY = priority;
                break;
        #endif  //TIMER2_DEVICE

        #ifdef TIMER4_DEVICE    
            case TIMER4_DEVICE:
                TIMER4_PRIORITY = priority;
                break;
        #endif  //TIMER4_DEVICE
    }
}

void clearTimer(uint8_t device) 
{
    switch (device) 
    {
        #ifdef TIMER1_DEVICE    
            case TIMER1_DEVICE:
                TIMER1_OCCURRED = FALSE;
                break;
        #endif  //TIMER1_DEVICE

        #ifdef TIMER2_DEVICE    
            case TIMER2_DEVICE:
                TIMER2_OCCURRED = FALSE;
                break;
        #endif  //TIMER2_DEVICE

        #ifdef TIMER4_DEVICE    
            case TIMER4_DEVICE:
                TIMER4_OCCURRED = FALSE;
                break;
        #endif  //TIMER4_DEVICE
    }
}


void startTimer(uint8_t device) 
{
    switch (device) 
    {
        #ifdef TIMER1_DEVICE    
            case TIMER1_DEVICE:
                TIMER1_ENABLE = TRUE;
                break;
        #endif  //TIMER1_DEVICE

        #ifdef TIMER2_DEVICE 
            case TIMER2_DEVICE:
                TIMER2_ENABLE = TRUE;
                break;
        #endif  //TIMER2_DEVICE

        #ifdef TIMER4_DEVICE    
            case TIMER4_DEVICE:
                TIMER4_ENABLE = TRUE;
                break;
        #endif  //TIMER4_DEVICE
    }
}


void stopTimer(uint8_t device) 
{
    switch (device) 
    {
        #ifdef TIMER1_DEVICE    
            case TIMER1_DEVICE:
                TIMER1_ENABLE = FALSE;
                break;
        #endif  //TIMER1_DEVICE

        #ifdef TIMER2_DEVICE 
            case TIMER2_DEVICE:
                TIMER2_ENABLE = FALSE;
                break;
        #endif  //TIMER2_DEVICE

        #ifdef TIMER4_DEVICE    
            case TIMER4_DEVICE:
                TIMER4_ENABLE = FALSE;
                break;
        #endif  //TIMER4_DEVICE
    }
}


uint16_t _getTimerPeriod(double timePeriod, uint8_t prescalerIndex) {
    return (unsigned int) ((timePeriod * 1000000) / (INSTRUCTION_PERIOD * PRESCALER_VALUES[prescalerIndex]));
}


uint16_t _getTimerPrescaler(double timePeriod) 
{
    unsigned char i;
    double exactTimerPrescaler;
    exactTimerPrescaler = (timePeriod * 1000000) / (INSTRUCTION_PERIOD * MAX_TIMER_PERIOD_VALUE);
    for (i = 0; i < sizeof(PRESCALER_VALUES) / 2; i += 1) {
        if ((int) exactTimerPrescaler < PRESCALER_VALUES[i]) {
            return i;
        }
    }
    i -= 1;
    //Using largest prescaler available, maximum timer value reached
    return i;
}
