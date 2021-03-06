/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Handles Quadrature Encoder inputs
 *
 * Switch is to be connected with PULLUP
 */

/** USAGE
 * 
 * 1. Declare qe_struct
 * 2. Load struct
 * 3. Each QE_UPDATE_RATE (ms) call qe_update. Usually put in timer interrupt handler
 * 4. Check result of qe_update. Pushing info is given by qe->pushed
 */

#ifndef QUADRATUREENCODER_H
#define QUADRATUREENCODER_H

#include "basic.h"

#define QE_UPDATE_RATE 2    // delta t between consecutive pinvalue checks

typedef enum {
    NONE, 
    PLUS_TICK,
    MINUS_TICK
} qe_RESULT;

typedef struct {
    pin pinA, pinB, pinSW;
    uint8_t oldA;
    uint16_t pushTicks, pushCounter;
    uint8_t pushed, changedA, changedSW;
} qe_struct;

void qe_loadStruct(qe_struct* qe, pin _pinA, pin _pinB, pin _pinSW, uint16_t pushedTime_s);

qe_RESULT qe_update(qe_struct* qe);

#endif //QUADRATUREENCODER_H