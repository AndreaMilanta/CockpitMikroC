/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Holds constants specific for the cockpit project
 */

#ifndef CKP_CONSTANTS_H
#define CKP_CONSTANTS_H

#include "ckp_canids.h"

/**
 * ILLUMINATION
 */ 
#define BACKLIGHT_MIN_DC 20     // minimum duty cycle (%) for backlight
#define BACKLIGHT_MAX_DC 100    // maximum duty cycle (%) for Backlight

/**
 * CAN
 */
// interesting values
#define IGNORED_BYTE_VALUE 0xAA     // value representing empty byte value in CAN packages: it is ignored
#define IGNORED_INT_VALUE (uint16_t)IGNORED_BYTE_VALUE << 8 & IGNORED_BYTE_VALUE    // value representing empty int value in CAN packages: it is ignored
#define TRIGGER_PLUS 0x01       // value representing a plus (positive trigger)
#define TRIGGER_MINUS 0x00      // value representing a minus (negative trigger)
#define TRIGGERED 0x00  // value represented a triggered event

//Policies
#define MSBYTE_FIRST TRUE   // Represents the (u)int16_t write policy on CAN

#endif // CKP_CONSTANTS_H