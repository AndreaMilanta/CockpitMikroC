/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Handles Quadrature Encoder inputs
 */

#ifndef QUADRATUREENCODER_H
#define QUADRATUREENCODER_H

#define ENCODER_DT 2  // delta t between consecutive pinvalue checks

typedef enum {
    NONE,
    PLUS,
    MINUS
} qe_RESULT;

typedef struct {
    uint8_t pinA, pinB, pinSW;
    uint16_t pushTicks, pushCounter;
    uint8_t pushed;
} qe_struct;

void qe_loadStruct(qe_struct* str, uint8_t pinA, uint8_t pinB, uint8_t pinSW, uint16_t pushedTime_s);

qe_RESULT update(void);

#endif //QUADRATUREENCODER_H