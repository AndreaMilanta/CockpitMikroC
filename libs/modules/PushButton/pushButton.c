/**
 * Author: Andrea Milanta
 * Created: 29/03/2018
 *
 * Simplifies push button handling
 */

#include "pushButton.h"


void pb_loadStruct(pb_struct* pb_str, pin p, uint16_t pushedTime_ms, uint8_t pullm)
{
    pb_str->pushpin = p;
    pb_str->tickPush = (pushedTime_ms < PB_MIN_DEBOUNCING_ms) ? PB_MIN_DEBOUNCING_ms / PB_UPDATE_RATE : pushedTime_ms / PB_UPDATE_RATE;
    pb_str->pullmode = pullm;
    pb_str->tickCounter = 0;
    pb_str->pushed = FALSE;
    pb_str->debouncing = FALSE;
}


uint8_t pb_update(pb_struct* pb_str)
{
    uint8_t read = (pb_str->pullmode == PULLUP) ? !readPin(pb_str->pushpin) : readPin(pb_str->pushpin);

    // not pushed
    if (!read) {
        // just stopped pushing
        if (pb_str->pushed || pb_str->debouncing) {
            pb_str->pushed = FALSE;
            pb_str->debouncing = FALSE;
            pb_str->triggered = FALSE;
            return PB_TRIGGER_UNPUSH;
        }
        // not pushed
        else
            return PB_UNPUSHED;
    }

    // just started pushing
    if (!pb_str->pushed || !pb_str->debouncing) {
        pb_str->tickCounter = pb_str->tickPush;
        pb_str->debouncing = TRUE;
        return PB_UNPUSHED;
    }

    // debouncing
    if (pb_str->debouncing && pb_str->tickCounter > 0) {
        pb_str->tickCounter -= 1;
        return PB_UNPUSHED;
    }

    // end of debouncing
    if (pb_str->debouncing && pb_str->tickCounter <= 0) {
        pb_str->debouncing = FALSE;
        pb_str->pushed = TRUE;
        return PB_TRIGGER_PUSH;
    }

    // pushing
    if (pb_str->pushed) {
        return PB_PUSHED;
    }
}
