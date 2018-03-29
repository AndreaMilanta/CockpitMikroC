/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * Simplifies push button handling
 */

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "basic.h"

#define PB_UPDATE_RATE 2
#define PB_MIN_DEBOUNCING_ms 30

#define PB_UNPUSHED 0
#define PB_PUSHED 1
#define PB_TRIGGER_PUSH 2
#define PB_TRIGGER_UNPUSH 3

typedef struct {
    pin pushpin;
    uint8_t pullmode;
    uint16_t tickPush;      // delta time (in ticks) before button is considered pushed
    uint16_t tickCounter;
    uint8_t pushed, debouncing, triggered;
} pb_struct;

void pb_loadStruct(pb_struct* pb_str, pin p, uint16_t pushedTime_ms, uint8_t pullm);

uint8_t pb_update(pb_struct* pb_str);

#endif //PUSHBUTTON_H
