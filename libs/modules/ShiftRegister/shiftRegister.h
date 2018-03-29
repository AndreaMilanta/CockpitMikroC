/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Library to handle communication with shift registers
 */

#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

#include "basic.h"

#define DT_us 1

#define MSB_FIRST 1
#define LSB_FIRST 0

void sr_shift8Out(pin dataPin, pin clockPin, pin latchPin, uint8_t value, uint8_t direction);

void sr_shift16Out(pin dataPin, pin clockPin, pin latchPin, uint16_t value, uint8_t direction);

void sr_shift28Out(pin dataPin, pin clockPin, pin latchPin, uint8_t value[], uint8_t direction);

#endif //SHIFTREGISTER_H