/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Define radiopanel ids for NAV2
 */

#ifndef CKP_NAV2_H
#define CKP_NAV2_H

#include "ckp_constants.h"
#include "sevenSegment.h"

#define CAN_ID NAV2_ID

// Display properties
#define COMM COMMON_CATHODE
#define DIGIT_NUM 5
#define DEC_LEN 2
#define FILLING_POLICY FILL

// CAN filters and masks
#define CAN_B1_MASK 0xFFFF
#define CAN_B1_FILTER_1 CAN_ID
#define CAN_B1_FILTER_2 0xFFFF
#define CAN_B2_MASK 0xFFFF
#define CAN_B2_FILTER_1 0xFFFF

#endif // CKP_NAV2_H