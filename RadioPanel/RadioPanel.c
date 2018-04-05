r/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * Code for single radio pl
 */

// microcontroller
#include "current.h"

// modules
#include "timers.h"
#include "can.h"
#include "pwm.h"
#include "sevenSegment.h"
#include "quadratureEncoder.h"
#include "pushButton.h"

// cockpit constants
#include "ckp_constants.h"

// Define the final panel (needed for CAN ID differences)
#include "comm1.h"
//include "comm2.h"
//include "nav1.h"
//include "nav2.h"

// backlight settings
#define BACKLIGHT_PWM_DEVICE PWM1_DEVICE

// Radio Properties
#define BCD_IN_CONV_MULTIPLIER 100

// Display properties
s7d_disp disp_act, disp_stb;

// Encoders properties
#define PUSHED_TIME 10 // duration in seconds for when pushed 
qe_struct qe_act, qe_stb;

// test button
#define TEST_INPUT_MODE PULLUP
pb_struct pb_test;

// test button
#define SWAP_INPUT_MODE PULLUP
pb_struct pb_swap;

// pins
pin dataPin, clockPin, act_ltc, stb_ltc;
pin qe1_pinA, qe1_pinB, qe1_pinSW, qe2_pinA, qe2_pinB, qe2_pinSW;
pin test_pin, swap_pin;

// counters
uint8_t s7d_counter;
uint8_t qe_counter;
uint8_t pb_counter;

// CAN
uint8_t can_tbs;    // signals whether there is a new data in can_in that needs to be sent (tbs)
uint8_t can_out[CAN_PACKET_SIZE];

// resets support variables for CAN
void resetCanArray(void)
{
    uint8_t i;
    for (i = 0; i < CAN_PACKET_SIZE; i++)
        can_out[i] = IGNORED_BYTE_VALUE;
    can_tbs = FALSE;
}

// setup function
void init(void) 
{
    can_masking can_mef;

    setAllPinAsDigital();

    // define pins with role (input/output)
    // seven segment display
    dataPin.port = &PORTE;    dataPin.pos = 2;      TRISE &= ~(1 << dataPin.pos);   //RE2
    clockPin.port = &PORTE;   clockPin.pos = 3;     TRISE &= ~(1 << clockPin.pos);  //RE3
    act_ltc.port = &PORTE;    act_ltc.pos = 4;      TRISE &= ~(1 << act_ltc.pos);   //RE4
    stb_ltc.port = &PORTE;    stb_ltc.pos = 5;      TRISE &= ~(1 << stb_ltc.pos);   //RE5
    // Encoders
    qe1_pinA.port = &PORTB;   qe1_pinA.pos = 0;     TRISB |= (1 << qe1_pinA.pos);   //RB0
    qe1_pinB.port = &PORTB;   qe1_pinB.pos = 1;     TRISB |= (1 << qe1_pinB.pos);   //RB1
    qe1_pinSW.port = &PORTB;  qe1_pinSW.pos = 2;    TRISB |= (1 << qe1_pinSW.pos);  //RB2
    qe2_pinA.port = &PORTB;   qe2_pinA.pos = 3;     TRISB |= (1 << qe2_pinA.pos);   //RB3
    qe2_pinB.port = &PORTB;   qe2_pinB.pos = 4;     TRISB |= (1 << qe2_pinB.pos);   //RB4
    qe2_pinSW.port = &PORTB;  qe2_pinSW.pos = 5;    TRISB |= (1 << qe2_pinSW.pos);  //RB5
    // Test button
    test_pin.port = &PORTD;   test_pin.pos = 1;     TRISD |= (1 << test_pin.pos);   //RD1
    swap_pin.port = &PORTD;   swap_pin.pos = 0;     TRISD |= (1 << swap_pin.pos);   //RD0


    // load display structs
    s7d_loadStruct(&disp_act, dataPin, clockPin, act_ltc, COMM, DIGIT_NUM, (1 << DEC_LEN));
    s7d_loadStruct(&disp_stb, dataPin, clockPin, stb_ltc, COMM, DIGIT_NUM, (1 << DEC_LEN));
    s7d_counter = S7D_UPDATE_RATE;

    // load encoders struct
    qe_loadStruct(&qe_act, qe1_pinA, qe1_pinB, qe1_pinSW, PUSHED_TIME);
    qe_loadStruct(&qe_stb, qe2_pinA, qe2_pinB, qe2_pinSW, PUSHED_TIME);
    qe_counter = QE_UPDATE_RATE;

    // push button struct
    pb_loadStruct(&pb_test, test_pin, IMMEDIATE, TEST_INPUT_MODE);
    pb_loadStruct(&pb_swap, swap_pin, IMMEDIATE, SWAP_INPUT_MODE);
    pb_counter = PB_UPDATE_RATE;

    // setup CAN
    can_mef.b1_mask = CAN_B1_MASK;
    can_mef.b1_filter_1 = CAN_B1_FILTER_1;
    can_mef.b1_filter_2 = CAN_B1_FILTER_2;
    can_mef.b2_mask = CAN_B2_MASK;
    can_mef.b2_filter_1 = CAN_B2_FILTER_1;
    can_init(CAN1_DEVICE, &can_mef);

    // setup PWM
    pwm_setup(BACKLIGHT_PWM_DEVICE, BACKLIGHT_FREQ, TIMER3_DEVICE);
    pwm_begin(BACKLIGHT_PWM_DEVICE);

    // setup timer
    setTimer(TIMER1_DEVICE, 0.001);
    startTimer(TIMER1_DEVICE);
}

void main() 
{
    init();
    while(1)
        Delay_ms(1000);
}

// generic 1ms interrupt
onTimer1Interrupt 
{
    clearTimer1();
    resetCanArray();
    s7d_counter--;
    qe_counter--;
    pb_counter--;

    // seven segment display handling
    if (s7d_counter) {
        s7d_update(&disp_act);
        s7d_update(&disp_stb);
        s7d_counter = S7D_UPDATE_RATE;
    }

    // encoder handling
    if (qe_counter) 
    {
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

    // buttons handling
    if (pb_counter) {
        // Test button
        switch (pb_update(&pb_test)) {
            case PB_TRIGGER_PUSH:
                disp_act.testing = TRUE;
                disp_stb.testing = TRUE;
                break;
            case PB_TRIGGER_UNPUSH:
                disp_act.testing = FALSE;
                disp_stb.testing = FALSE;
                break;
        }

        // Swap button
        if (pb_update(&pb_swap) == PB_TRIGGER_PUSH) {
            can_out[STB_ACT_SWAP] = TRIGGERED;
            can_tbs = TRUE;
        }

        pb_counter = PB_UPDATE_RATE;
    }

    // send updates on CAN
    if (can_tbs)
        can_write(CAN1_DEVICE, CAN_ID, can_out, CAN_PRIORITY_MEDIUM);
}

onCan1Interrupt 
{
    // CAN handling variables
    uint32_t id;
    uint16_t dataLen, flags;
    uint8_t can_in[CAN_PACKET_SIZE];

    // display variables
    uint16_t act, stb;
    uint32_t act_dec, stb_dec;
    double act_dbl, stb_dbl;

    // backlight variables
    uint8_t bckl;

    // CAN reading
    can1_clearInterrupt();
    can1_read(&id, can_in, &dataLen, &flags);

    // Packages are always full. If not its erroneus
    if (dataLen < CAN_PACKET_SIZE)
        return;

    switch (id) 
    {
        // new display info
        case CAN_ID:
            act = MSBYTE_FIRST ? (uint16_t) (can_in[ACT_DISP] << 8) & can_in[ACT_DISP + 1] \
                               : (uint16_t) (can_in[ACT_DISP + 1] << 8) & can_in[ACT_DISP];
            stb = MSBYTE_FIRST ? (uint16_t) (can_in[STB_DISP] << 8) & can_in[STB_DISP + 1] \
                               : (uint16_t) (can_in[STB_DISP + 1] << 8) & can_in[STB_DISP];
            if (act != IGNORED_INT_VALUE){
                act_dec = Bcd2Dec(act);
                act_dbl = (double) act_dec / BCD_IN_CONV_MULTIPLIER;
                s7d_writeDouble(&disp_act, act_dbl, DEC_LEN, FILLING_POLICY);
            }
            if (stb != IGNORED_INT_VALUE){
                stb_dec = Bcd2Dec(stb);
                stb_dbl = (double) stb_dec / BCD_IN_CONV_MULTIPLIER;
                s7d_writeDouble(&disp_stb, stb_dbl, DEC_LEN, FILLING_POLICY);
            }
            break;

        // Backlight id
        case BACKLIGHT_ID:
            bckl = can_in[BACKLIGHT_POS];
            if (bckl != IGNORED_BYTE_VALUE){
                if (bckl < BACKLIGHT_MIN_DC)
                    bckl = BACKLIGHT_MIN_DC;
                if (bckl > BACKLIGHT_MAX_DC)
                    bckl = BACKLIGHT_MAX_DC;
                pwm_setDuty(BACKLIGHT_PWM_DEVICE, bckl);
            }
            break;
        // Unexpected packet
        default: 
            return;
    }

}
