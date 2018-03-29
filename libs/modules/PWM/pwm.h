/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * PWM managment
 */

#ifndef PWM_H
#define PWM_H

#include "basic.h"
#include "current.h"

void pwm_setup(uint8_t device, uint16_t freq, uint8_t timer_device);

void pwm_begin(uint8_t device);

void pwm_end(uint8_t device);

void pwm_setDuty(uint8_t device, uint8_t dc);

uint16_t _getPWMPrescaler(uint16_t freq);

#endif //PWM_H