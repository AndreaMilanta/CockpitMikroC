/**
 * Author: Andrea Milante
 * Created: 28/03/2018
 *
 * Library to handle sevensegment display connected as default connection
 */

#ifndef SEVENSEGMENT_H
#define SEVENSEGMENT_H

#include "shiftRegister.h"

#define SEVEN_SEG_UPDATE_RATE 15
#define MAX_DIGIT 5

// Digits
#define ZERO  0xFC
#define ONE 0x60
#define TWO 0xDA
#define THREE 0xF2
#define FOUR 0x66
#define FIVE 0xB6
#define SIX 0xBE
#define SEVEN 0xE0
#define EIGHT 0xFE
#define NINE 0xF6
#define A 0xEE
#define B 0x3E
#define C 0x9C
#define D 0x7A
#define E 0x9E
#define F 0x8E
#define MINUS 0x02       // '-' char 
#define OFF 0x00

#define COMMON_CATHODE 0
#define COMMON_ANODE 1

#define FILL 0
#define NOFILL 1

typedef enum {
    WITH_COMMA,
    WITHOUT_COMMA
} COMMA;

typedef struct {
    uint8_t dataPin;
    uint8_t clockPin;
    uint8_t latchPin;
    uint8_t comm;
    uint8_t digitNum;
    uint8_t currDigit;
    uint8_t datas[MAX_DIGIT];
} s7d_disp;


void s7d_loadStruct(s7d_disp *disp, uint8_t dPin, uint8_t cPin, uint8_t lPin, uint8_t c, uint8_t dNum);

uint8_t ssd_digitToByte(uint8_t value, uint8_t common, COMMA comma);

void s7d_update(s7d_disp disp);

void s7d_writeInt(s7d_disp disp, int32_t value, uint8_t fill);

void s7d_writeDouble(s7d_disp disp, double value, uint8_t decLen, uint8_t fill);

#endif //SEVENSEGMENT_H