/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Handles Quadrature Encoder inputs
 */

#include "quadratureEncoder.h"

void qe_loadStruct(qe_struct* qe, pin _pinA, pin _pinB, pin _pinSW, uint16_t pushedTime_s)
{
    qe->pinA = _pinA;
    qe->oldA = readPin(qe->pinA);
    qe->pinB = _pinB;
    qe->pinSW = _pinSW;
    qe->pushTicks = pushedTime_s * 1000 / QE_UPDATE_RATE;
    qe->pushed = FALSE;
    qe->pushCounter = 0;
    qe->changedA = FALSE;
    qe->changedSW = FALSE;
}

// Check if the encoder has moved. If so return true
qe_RESULT qe_update(qe_struct* qe)
{
    qe_RESULT result = NONE;
    uint8_t a = readPin(*qe->pinA);
    uint8_t b = readPin(*qe->pinB);
    uint8_t sw = readPin(*qe->pinSW);

    // Handle Switch
    if (!sw && qe->changedSW) {
        qe->pushCounter = qe->pushTicks;
        qe->pushed = TRUE;
    }
    else {
        if (qe->pushCounter > 0 && qe->pushed)
            qe->pushCounter--;
        else
            qe->pushed = FALSE;
    }
    qe->changedSW = sw ? FALSE : TRUE;

    // Handle Encoder
    if (qe->changedA)
    {
        if (a == qe->oldA && a)
            result = b ? PLUS_TICK : MINUS_TICK;
        qe->changedA = FALSE;
    }
    else
    {
        if (a != qe->oldA)
            qe->changedA = TRUE;
    }
    qe->oldA = a;
    return result;
}