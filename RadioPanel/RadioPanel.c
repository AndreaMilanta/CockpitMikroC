/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * Code for single radio panel
 */

// microcontroller
#include "dsPIC30F4012.h"

// modules
// #include "shiftRegister.h"
#include "sevenSegment.h"

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

// quick access pin
#define DATA_PIN PORTB.B0
#define CLOCK_PIN PORTB.B1
#define ACT_LTC PORTB.B2
#define STB_LTC PORTB.B3

s7d_disp disp_act, disp_stb;

// setup function
void setup() {
    // load display structs
    s7d_loadStruct(&disp_act, DATA_PIN, CLOCK_PIN, ACT_LTC, COMM, DIGIT_NUM);
    s7d_loadStruct(&disp_stb, DATA_PIN, CLOCK_PIN, STB_LTC, COMM, DIGIT_NUM);

    // sets the display pin as output
    TRISB &= 0xF0;  
}

void main() 
{
    setup();
}