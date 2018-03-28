/**
 * Author: Andrea Milante
 * Created: 28/03/2018
 *
 * Library to handle sevensegment display connected as default connection
 */

#include "sevenSegment.h"

// loads the struct
void s7d_loadStruct(s7d_disp *disp, uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t c, uint8_t dNum)
{
    disp->dataPin = dPin;
    disp->clockPin = cPin;
    disp->latchPin = lPin;
    disp->digitNum = dNum;
    disp->comm = c;
    disp->currDigit = 0;
}

// convert from digit to led segments array
uint8_t digitToByte(int value, uint8_t common, COMMA comma)
{
    uint8_t digit;
    switch (value) {
        case -1:
            digit = MINUS;
            break;
        case 0:
            digit = ZERO;
            break;
        case 1:
            digit = ONE;
            break;
        case 2:
            digit = TWO;
            break;
        case 3:
            digit = THREE;
            break;
        case 4:
            digit = FOUR;
            break;
        case 5:
            digit = FIVE;
            break;
        case 6:
            digit = SIX;
            break;
        case 7:
            digit = SEVEN;
            break;
        case 8:
            digit = EIGHT;
            break;
        case 9:
            digit = NINE;
            break;
        case 0xA:
            digit = A;
            break;
        case 0xB:
            digit = B;
            break;
        case 0xC:
            digit = C;
            break;
        case 0xD:
            digit = D;
            break;
        case 0xE:
            digit = E;
            break;
        case 0xF:
            digit = F;
            break;
        default:
            digit = OFF;
    }
    if (comma == WITH_COMMA)
        digit |= 0x01;      // add comma bit
    if (common == COMMON_ANODE)
        digit = ~digit;
    return digit;
}


// function to be called to keep the 7seg display drawn
void s7d_update(s7d_disp* disp)
{
    uint8_t values[2];
    uint8_t digits = 1 << (7 - disp->currDigit);
    if (disp->comm == COMMON_CATHODE)
        digits = ~digits;
    values[0] = disp->datas[disp->currDigit];
    values[1] = digits;
    sr_shift28Out(disp->dataPin, disp->clockPin, disp->latchPin, values, LSB_FIRST);
    disp->currDigit++;
    if (disp->currDigit >= disp->digitNum)
        disp->currDigit = 0;
}

// writes a double on the 7seg display
void s7d_writeDouble(s7d_disp* disp, double value, uint8_t decLen, uint8_t fill)
{
    uint8_t i;
    uint8_t neg = (value < 0);      //is negtative
    uint8_t comma = FALSE;          // write comma?
    uint8_t minus = 0;                  //used to balance the '-' as first char 
    uint32_t intValue;
    value = neg ? value * -1 : value;
    for (i = 0; i < decLen; i++)
        value *= 10;
    intValue = (uint32_t)value;
    // put '-' as first char if is neg and fill is true
    if (neg && fill) {
        disp->datas[0] = digitToByte(-1, disp->comm, WITHOUT_COMMA);
        minus++;
        neg = FALSE;
    }
    for (i = 1; i <= disp->digitNum - minus; i++) 
    {
        uint32_t v = intValue % 10;
        if (intValue == 0 && i > decLen + 1) {   // write '-' as soon as the significamtful digits are done
            if (neg) {
                v = -1;
                neg = FALSE;
            }
            else {
                if (fill == FILL) // write '0' if the original value is 0 or to fill
                    v = 0;
                else
                    v = 100;                // Invalid value -> empty digit
            }
        }
        if (i == decLen + 1)
            comma = WITH_COMMA;
        disp->datas[disp->digitNum - i] = digitToByte(v, disp->comm, comma);
        intValue /= 10;
        comma = FALSE;
    }
}


void s7d_writeInt(s7d_disp* disp, int32_t value, uint8_t fill)
{
    uint8_t i;
    uint8_t neg = (value < 0);      //is negtative
    uint8_t minus = 0;                  //used to balance the '-' as first char 
    value = neg ? value * -1 : value;
    // put '-' as first char if is neg and fill is true
    if (neg && fill) {
        disp->datas[0] = digitToByte(-1, disp->comm, FALSE);
        minus++;
        neg = FALSE;
    }
    for (i = 1; i <= disp->digitNum - minus; i++) 
    {
        int v = value % 10;
        if (value == 0) {   // write '-' as soon as the significant digits are done
            if (neg) {
                v = -1;
                neg = FALSE;
            }
            else {
                if (fill == FILL || i == 1) // write '0' if the original value is 0 or to fill
                    v = 0;
                else
                    v = 100;                // Invalid value -> empty digit
            }
        }
        disp->datas[disp->digitNum - i] = digitToByte(v, disp->comm, FALSE);
        value /= 10;
    }
}