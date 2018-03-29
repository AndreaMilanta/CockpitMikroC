/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * PWM managment
 */

#include "pwm.h"

#ifdef PWM1_DEVICE
    uint16_t _pwm1_timerPeriod;
#endif //PWM1_DEVICE

#ifdef PWM2_DEVICE
    uint16_t _pwm2_timerPeriod;
#endif //PWM2_DEVICE

#ifdef PWM3_DEVICE
    uint16_t _pwm3_timerPeriod;
#endif //PWM3_DEVICE

void pwm_setup(uint8_t device, uint16_t freq, uint8_t timer_device)
{
    uint8_t timer;
    uint16_t prescalerIndex;

    prescalerIndex = _getPWMPrescaler(freq);

    // timer mapping
    switch(timer_device)
    {
        #ifdef TIMER2_DEVICE
            case TIMER2_DEVICE:
                timer = 2;
                break;
        #endif //TIMER2_DEVICE

        #ifdef TIMER3_DEVICE
            case TIMER3_DEVICE:
                timer = 3;
                break;
        #endif //TIMER3_DEVICE

        default:
            return;
    }

    switch(device)
    {
        #ifdef PWM1_DEVICE
            case PWM1_DEVICE:
                _pwm1_timerPeriod = PWM_Init(freq, 1, PRESCALER_VALUES[prescalerIndex], timer);
                break;
        #endif //PWM1_DEVICE

        #ifdef PWM2_DEVICE
            case PWM2_DEVICE:
                _pwm2_timerPeriod = PWM_Init(freq, 2, PRESCALER_VALUES[prescalerIndex], timer);
                break;
        #endif //PWM2_DEVICE

        #ifdef PWM3_DEVICE
            case PWM3_DEVICE:
                _pwm3_timerPeriod = PWM_Init(freq, 3, PRESCALER_VALUES[prescalerIndex], timer);
                break;
        #endif //PWM3_DEVICE
    }
}


void pwm_begin(uint8_t device)
{
    switch(device)
    {
        #ifdef PWM1_DEVICE
            case PWM1_DEVICE:
                PWM_Start(1);
                break;
        #endif //PWM1_DEVICE

        #ifdef PWM2_DEVICE
            case PWM2_DEVICE:
                PWM_Start(2);
                break;
        #endif //PWM2_DEVICE

        #ifdef PWM3_DEVICE
            case PWM3_DEVICE:
                PWM_Start(3);
                break;
        #endif //PWM3_DEVICE
    }
}


void pwm_end(uint8_t device)
{
    switch(device)
    {
        #ifdef PWM1_DEVICE
            case PWM1_DEVICE:
                PWM_Stop(1);
                break;
        #endif //PWM1_DEVICE

        #ifdef PWM2_DEVICE
            case PWM2_DEVICE:
                PWM_Stop(2);
                break;
        #endif //PWM2_DEVICE

        #ifdef PWM3_DEVICE
            case PWM3_DEVICE:
                PWM_Stop(3);
                break;
        #endif //PWM3_DEVICE
    }
}


void pwm_setDuty(uint8_t device, uint8_t dc)
{
    uint16_t duty;
    switch(device)
    {
        #ifdef PWM1_DEVICE
            case PWM1_DEVICE:
                duty = _pwm1_timerPeriod * 100 / dc;
                PWM_Set_Duty(duty, 1);
                break;
        #endif //PWM1_DEVICE

        #ifdef PWM2_DEVICE
            case PWM2_DEVICE:
                duty = _pwm2_timerPeriod * 100 / dc;
                PWM_Set_Duty(duty, 2);
                break;
        #endif //PWM2_DEVICE

        #ifdef PWM3_DEVICE
            case PWM3_DEVICE:
                duty = _pwm3_timerPeriod * 100 / dc;
                PWM_Set_Duty(duty, 3);
                break;
        #endif //PWM3_DEVICE
    }
}


uint16_t _getPWMPrescaler(uint16_t freq) 
{
    uint8_t i;
    double exactTimerPrescaler = (double)(1000000) / (freq * INSTRUCTION_PERIOD * MAX_TIMER_PERIOD_VALUE);
    for (i = 0; i < sizeof(PRESCALER_VALUES) / 2; i += 1) {
        if ((int) exactTimerPrescaler < PRESCALER_VALUES[i]) {
            return i;
        }
    }
    i -= 1;
    //Using largest prescaler available, maximum timer value reached
    return i;
}
