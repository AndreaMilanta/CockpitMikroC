/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * Code for single radio panel
 */

// microcontroller
#include "dsPIC30F4012.h"

// modules
#include "sevenSegment.h"
#include "quadratureEncoder.h"

// cockpit constants
#include "ckp_constants.h"

// Define the final panel (needed for CAN ID differences)
#include "comm1.h"
//include "comm2.h"
//include "nav1.h"
//include "nav2.h"

// Display properties
#define DIGIT_NUM 5
#define COMM COMMON_CATHODE
s7d_disp disp_act, disp_stb;

// Encoders properties
#define PUSHED_TIME 10 // duration in seconds for when pushed 
qe_struct qe_act, qe_stb;

// pins
pin dataPin, clockPin, act_ltc, stb_ltc, qe1_pinA, qe1_pinB, qe1_pinSW, qe2_pinA, qe2_pinB, qe2_pinSW;

// counter
uint8_t s7d_counter;
uint8_t qe_counter;

// CAN
uint8_t can_tbs;    // signals whether there is dìnew data in can_in that needs to be sent (tbs)
uint8_t can_out[8];
uint16_t can_in[4];

// resets support variables for CAN
void can_resetSupport(void)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
        can_out[i] = IGNORED_BYTE_VALUE;
    can_tbs = FALSE;
}

// setup function
void init(void) {
    // Set all pin as digital
    ADPCFG = 0xFFFF;

    // define pins with role (input - output)
    // seven segment display
    dataPin.port = &PORTE;    dataPin.pos = 0;      TRISE &= ~(1 << dataPin.pos);   //RE0
    clockPin.port = &PORTE;   clockPin.pos = 1;     TRISE &= ~(1 << clockPin.pos);  //RE1
    act_ltc.port = &PORTE;    act_ltc.pos = 2;      TRISE &= ~(1 << act_ltc.pos);   //RE2
    stb_ltc.port = &PORTE;    stb_ltc.pos = 3;      TRISE &= ~(1 << stb_ltc.pos);   //RE3
    // Encoders
    qe1_pinA.port = &PORTB;   qe1_pinA.pos = 0;     TRISB |= (1 << qe1_pinA.pos);   //RB0
    qe1_pinB.port = &PORTB;   qe1_pinB.pos = 1;     TRISB |= (1 << qe1_pinB.pos);   //RB1
    qe1_pinSW.port = &PORTB;  qe1_pinSW.pos = 2;    TRISB |= (1 << qe1_pinSW.pos);  //RB2
    qe2_pinA.port = &PORTB;   qe2_pinA.pos = 3;     TRISB |= (1 << qe2_pinA.pos);   //RB3
    qe2_pinB.port = &PORTB;   qe2_pinB.pos = 4;     TRISB |= (1 << qe2_pinB.pos);   //RB4
    qe2_pinSW.port = &PORTB;  qe2_pinSW.pos = 5;    TRISB |= (1 << qe2_pinSW.pos);  //RB5

    // load display structs
    s7d_loadStruct(&disp_act, dataPin, clockPin, act_ltc, COMM, DIGIT_NUM);
    s7d_loadStruct(&disp_stb, dataPin, clockPin, stb_ltc, COMM, DIGIT_NUM);
    s7d_counter = S7D_UPDATE_RATE;

    // load encoders struct
    qe_loadStruct(&qe_act, qe1_pinA, qe1_pinB, qe1_pinSW, PUSHED_TIME);
    qe_loadStruct(&qe_stb, qe2_pinA, qe2_pinB, qe2_pinSW, PUSHED_TIME);
    qe_counter = QE_UPDATE_RATE;

    // setup timer
    setTimer(TIMER1_DEVICE, 0.001);
    setInterruptPriority(TIMER1_DEVICE, MEDIUM_PRIORITY);

    // setup CAN
    can_resetSupport();
}

void main() 
{
    init();
    while(1)
        Delay_ms(1000);
}

// generic 1ms interrupt
onTimer1Interrupt {
    clearTimer1();
    can_resetSupport();
    s7d_counter--;
    qe_counter--;

    // seven segment display handling
    if (s7d_counter) {
        s7d_update(&disp_act);
        s7d_update(&disp_stb);
        s7d_counter = S7D_UPDATE_RATE;
    }

    // encoder handling
    if (qe_counter) {
        // active encoder handling
        qe_RESULT res = qe_update(&qe_act);
        if (res != NONE)
            can_tbs = TRUE;
        if (qe_act.pushed && res != NONE)
            can_out[ACT_DEC_DELTA] = (res == PLUS_TICK) ? TRIGGER_PLUS : TRIGGER_MINUS;
        if (!qe_act.pushed && res != NONE)
            can_out[ACT_INT_DELTA] = (res == PLUS_TICK) ? TRIGGER_PLUS : TRIGGER_MINUS;

        // standby encoder handling
        res = qe_update(&qe_stb);
        if (res != NONE)
            can_tbs = TRUE;
        if (qe_stb.pushed && res != NONE)
            can_out[STB_DEC_DELTA] = (res == PLUS_TICK) ? TRIGGER_PLUS : TRIGGER_MINUS;
        if (!qe_stb.pushed && res != NONE)
            can_out[STB_INT_DELTA] = (res == PLUS_TICK) ? TRIGGER_PLUS : TRIGGER_MINUS;

        qe_counter = QE_UPDATE_RATE;
    }
}
