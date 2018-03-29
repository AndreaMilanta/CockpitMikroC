/** 
 * Author: Andrea Milanta
 * Created 29/03/2018
 *
 * Holds all those libraries that may change depending on the ucontroller and that are needed by varius libraries
 */

#ifndef CURRENT_H
#define CURRENT_H

 #include "basic.h"

 // Frequency - REQUIRED!!!!!!!
 #define OSC_FREQ_MHZ 80
 #define INSTRUCTION_PERIOD 4.0 / OSC_FREQ_MHZ
 
 // Actually declared in specific ucontroller.c file
 extern const unsigned int PRESCALER_VALUES[];
 
 // microcontroller - REQUIRED
 #include "dsPIC30F4012.h"

#endif //CURRENT_H