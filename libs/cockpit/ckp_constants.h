/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Holds constants specific for the cockpit project
 */

#ifndef CKP_CONSTANTS_H
#define CKP_CONSTANTS_H

#include "ckp_canids.h"

// CAN interesting values
#define IGNORED_INT_VALUE 0xAAAA    // value representing empty int value in CAN packages: it is ignored
#define IGNORED_BYTE_VALUE 0xAA     // value representing empty byte value in CAN packages: it is ignored
#define TRIGGER_PLUS 0x01       // value representing a plus (positive trigger)
#define TRIGGER_MINUS 0x00      // value representing a minus (negative trigger)
#define TRIGGERED 0x00  // value represented a triggered event

#endif // CKP_CONSTANTS_H