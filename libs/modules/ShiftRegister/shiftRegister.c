/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Library to handle communication with shift registers
 */

#include "shiftRegister.h"

// shifts one byte (data) out
void sr_shift8Out(pin dataPin, pin clockPin, pin latchPin, uint8_t value, uint8_t direction)
{
    uint8_t i;
    setLow(clockPin);   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            (value << i) & 0x80 ? setHigh(dataPin) : setLow(dataPin); 
        else
            (value << i) & 0x01 ? setHigh(dataPin) : setLow(dataPin); 
        setHigh(clockPin);
        delay_us(DT_us);
        setLow(clockPin);
        delay_us(DT_us);
    }
    setHigh(latchPin);
    delay_us(DT_us);
    setLow(latchPin);
    delay_us(DT_us);
}

// shifts one int (two bytes - data) out
void sr_shift16Out(pin dataPin, pin clockPin, pin latchPin, uint16_t value, uint8_t direction)
{
    uint8_t i;
    setLow(clockPin);   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 16; i++)
    {
        if (direction == MSB_FIRST)
            (value << i) & 0x80 ? setHigh(dataPin) : setLow(dataPin); 
        else
            (value << i) & 0x01 ? setHigh(dataPin) : setLow(dataPin); 
        setHigh(clockPin);
        delay_us(DT_us);
        setLow(clockPin);
        delay_us(DT_us);
    }
    setHigh(latchPin);
    delay_us(DT_us);
    setLow(latchPin);
    delay_us(DT_us);
}

// shifts two bytes out (data) out
// data must be an array of size 2 - NO CHECKING!!!
// value[0] is always shifted out before value[1] regardless of direction
void sr_shift28Out(pin dataPin, pin clockPin, pin latchPin, uint8_t value[], uint8_t direction)
{
    uint8_t i;
    setLow(clockPin);   //initially the clock is set to 0
    delay_us(DT_us);
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            (value[0] << i) & 0x80 ? setHigh(dataPin) : setLow(dataPin); 
        else
            (value[0] << i) & 0x01 ? setHigh(dataPin) : setLow(dataPin); 
        setHigh(clockPin);
        delay_us(DT_us);
        setLow(clockPin);
        delay_us(DT_us);
    }
    for (i = 0; i < 8; i++)
    {
        if (direction == MSB_FIRST)
            (value[1] << i) & 0x80 ? setHigh(dataPin) : setLow(dataPin); 
        else
            (value[1] << i) & 0x01 ? setHigh(dataPin) : setLow(dataPin); 
        setHigh(clockPin);
        delay_us(DT_us);
        setLow(clockPin);
        delay_us(DT_us);
    }
    setHigh(latchPin);
    delay_us(DT_us);
    setLow(latchPin);
    delay_us(DT_us);
}
