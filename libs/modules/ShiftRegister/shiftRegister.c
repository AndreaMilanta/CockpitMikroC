/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Library to handle communication with shift registers
 */

#include "shiftRegister.h"

// shifts one byte (data) out
void sr_shift8Out(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t value, uint8_t direction)
{
    uint8_t i;
    clockPin = LOW;   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            dataPin = (value << i) & 0x80 ? HIGH : LOW; 
        else
            dataPin = (value >> i) & 0x01;
        clockPin = HIGH;
        delay_us(DT_us);
        clockPin = LOW;
        delay_us(DT_us);
    }
    latchPin = HIGH;
    delay_us(DT_us);
    latchPin = LOW;
    delay_us(DT_us);
}

// shifts one int (two bytes - data) out
void sr_shift16Out(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint16_t value, uint8_t direction)
{
    uint8_t i;
    clockPin = LOW;   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 16; i++)
    {
        if (direction == MSB_FIRST)
            dataPin = (value << i) & 0x8000 ? HIGH : LOW; 
        else
            dataPin = (value >> i) & 0x0001;
        clockPin = HIGH;
        delay_us(DT_us);
        clockPin = LOW;
        delay_us(DT_us);
    }
    latchPin = HIGH;
    delay_us(DT_us);
    latchPin = LOW;
    delay_us(DT_us);
}

// shifts two bytes out (data) out
// data must be an array of size 2 - NO CHECKING!!!
// value[0] is always shifted out before value[1] regardless of direction
void sr_shift28Out(uint8_t dataPin, uint8_t clockPin, uint8_t latchPin, uint8_t value[], uint8_t direction)
{
    uint8_t i;
     clockPin = LOW;   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            dataPin = (value[0] << i) & 0x80 ? HIGH : LOW; 
        else
            dataPin = (value[0] >> i) & 0x01;
        clockPin = HIGH;
        delay_us(DT_us);
        clockPin = LOW;
        delay_us(DT_us);
    }
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            dataPin = (value[1] << i) & 0x80 ? HIGH : LOW; 
        else
            dataPin = (value[1] >> i) & 0x01;
        clockPin = HIGH;
        delay_us(DT_us);
        clockPin = LOW;
        delay_us(DT_us);
    }
    latchPin = HIGH;
    delay_us(DT_us);
    latchPin = LOW;
    delay_us(DT_us);   
}
