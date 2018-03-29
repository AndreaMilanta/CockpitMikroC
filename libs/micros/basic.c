/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * List of Basic definitions for any PIC project
 */

#include "basic.h"

 void setLow(pin p)
{
    *(p.port) &= ~(1 << p.pos); 
}

 void setHigh(pin p)
{
    *(p.port) |= 1 << p.pos;
}

 uint8_t readPin(pin p)
{
    return *(p.port) & (1 << p.pos) ? 1 : 0;
}
