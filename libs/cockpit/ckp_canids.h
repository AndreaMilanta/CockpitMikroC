/**
 * Author: Andrea Milanta
 * Created: 28/03/2018
 *
 * Holds can ids specific for the cockpit project
 */

#ifndef CKP_CANIDS_H
#define CKP_CANIDS_H

/**
 * ILLUMINATION
 */
#define BACKLIGHT_ID 0b00000000000
#define BACKLIGHT_POS 0     // value is represented as percentage on byte 0

/**
 * RADIOS
 */
// ids
#define COMM1_ID 0b00000000000
#define COMM2_ID 0b00000000000
#define NAV1_ID 0b00000000000
#define NAV2_ID 0b00000000000

// Position of data in package
#define ACT_DISP 0            // position in package (int, occupied two bytes)      // to panel
#define STB_DISP 2            // position in package (int, occupies two bytes)      // to panel
#define STB_ACT_SWAP 0        // position in package (byte)     // to FSX
#define ACT_INT_DELTA 1       // position in package (byte)     // to FSX
#define ACT_DEC_DELTA 2       // position in package (byte)     // to FSX
#define STB_INT_DELTA 3       // position in package (byte)     // to FSX
#define STB_DEC_DELTA 4       // position in package (byte)     // to FSX


#endif // CKP_CANIDS_H