/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * holds definitions and main setup functions for the dsPIC30F4012 microcontroller
 */
 
#include "dsPIC30F4012.h"

//const double INSTRUCTION_PERIOD = 4.0 / OSC_FREQ_MHZ;
const unsigned int PRESCALER_VALUES[] = {1, 8, 64, 256};

void setAllPinAsDigital(void) {
    ADPCFG = 0xFFFF;
}

void setExternalInterruptPriority(unsigned char device, unsigned char priority) {
    switch (device) {
        case INT0_DEVICE:
            INT0_PRIORITY = priority;
            break;
        case INT1_DEVICE:
            INT1_PRIORITY = priority;
            break;
        case INT2_DEVICE:
            INT2_PRIORITY = priority;
            break;
        case TIMER1_DEVICE:
            TIMER1_PRIORITY = priority;
            break;
        case TIMER2_DEVICE:
            TIMER2_PRIORITY = priority;
            break;
        case TIMER4_DEVICE:
            TIMER4_PRIORITY = priority;
            break;
        default:
            break;
    }
}

void setExternalInterrupt(unsigned char device, char edge) {
    setExternalInterruptPriority(device, MEDIUM_PRIORITY);
    switch (device) {
        case INT0_DEVICE:
            INT0_TRIGGER_EDGE = edge;
            INT0_OCCURRED = FALSE;
            INT0_ENABLE = TRUE;
            break;
        case INT1_DEVICE:
            INT1_TRIGGER_EDGE = edge;
            INT1_OCCURRED = FALSE;
            INT1_ENABLE = TRUE;
            break;
        case INT2_DEVICE:
            INT2_TRIGGER_EDGE = edge;
            INT2_OCCURRED = FALSE;
            INT2_ENABLE = TRUE;
            break;
        default:
            break;
    }
}

void switchExternalInterruptEdge(unsigned char device) {
    switch (device) {
        case INT0_DEVICE:
            if (INT0_TRIGGER_EDGE == FALLING_EDGE) {
                INT0_TRIGGER_EDGE = RISING_EDGE;
            } else {
                INT0_TRIGGER_EDGE = FALLING_EDGE;
            }
            break;
        case INT1_DEVICE:
            if (INT1_TRIGGER_EDGE == FALLING_EDGE) {
                INT1_TRIGGER_EDGE = RISING_EDGE;
            } else {
                INT1_TRIGGER_EDGE = FALLING_EDGE;
            }
            break;
        case INT2_DEVICE:
            if (INT2_TRIGGER_EDGE == FALLING_EDGE) {
                INT2_TRIGGER_EDGE = RISING_EDGE;
            } else {
                INT2_TRIGGER_EDGE = FALLING_EDGE;
            }
            break;
        /*
        case INT4_DEVICE:
            if (INT4_TRIGGER_EDGE == NEGATIVE_EDGE) {
                INT4_TRIGGER_EDGE = POSITIVE_EDGE;
            } else {
                INT4_TRIGGER_EDGE = NEGATIVE_EDGE;
            }
        */
        default:
            break;
    }
}

char getExternalInterruptEdge(unsigned char device) {
    switch (device) {
        case INT0_DEVICE:
            return INT0_TRIGGER_EDGE;
        case INT1_DEVICE:
            return INT1_TRIGGER_EDGE;
        case INT2_DEVICE:
            return INT2_TRIGGER_EDGE;
        /*
        case INT4_DEVICE:
            return INT4_TRIGGER_EDGE;
        */
        default:
            return 0;
    }
}

void clearExternalInterrupt(unsigned char device) {
    switch (device) {
        case INT0_DEVICE:
            INT0_OCCURRED = FALSE;
            break;
        case INT1_DEVICE:
            INT1_OCCURRED = FALSE;
            break;
        case INT2_DEVICE:
            INT2_OCCURRED = FALSE;
            break;
        default:
            break;
    }
}

void setupAnalogSampling(void) {
    ANALOG_CONVERSION_TRIGGER_SOURCE = ACTS_AUTOMATIC;
    ANALOG_DATA_OUTPUT_FORMAT = ADOF_UNSIGNED_INTEGER;
    ANALOG_IDLE_ENABLE = FALSE;
    ANALOG_CH0_SCAN_ENABLE = TRUE;
    ANALOG_BUFFER_SIZE = ABS_16BIT;
    ANALOG_ENABLE_ALTERNATING_MULTIPLEXER = FALSE;
    ANALOG_CLOCK_SOURCE = ACS_EXTERNAL;
    ANALOG_CHANNEL_B_NEGATIVE_INPUT = ACNI_VREF;
    ANALOG_CHANNEL_A_NEGATIVE_INPUT = ACNI_VREF;
    ANALOG_CHANNEL_B_POSITIVE_INPUT = 0;
    ANALOG_CHANNEL_A_POSITIVE_INPUT = 0;

    //Setting clock conversion in order to have the minimum TAD possible
    ANALOG_CLOCK_CONVERSION = getMinimumAnalogClockConversion();
    ANALOG_AUTOMATIC_SAMPLING_TADS_INTERVAL = 1;

    ANALOG_MODE_PORT = 0b1111111111111111; //All analog inputs are disabled
    ANALOG_SCAN_PORT = 0; //Skipping pin scan

    setAutomaticSampling();
    setAnalogVoltageReference(AVR_AVDD_AVSS);
    unsetAnalogInterrupt();
    startSampling();
}

void turnOnAnalogModule() {
    ANALOG_SAMPLING_ENABLE = TRUE;
}

void turnOffAnalogModule() {
    ANALOG_SAMPLING_ENABLE = FALSE;
}

void startSampling(void) {
    ANALOG_SAMPLING_STATUS = TRUE;
}

unsigned int getAnalogValue(void) {
    return ANALOG_BUFFER0;
}

void setAnalogPIN(unsigned char pin) {
    ANALOG_MODE_PORT = ANALOG_MODE_PORT & ~(int) (TRUE << pin);
    ANALOG_SCAN_PORT = ANALOG_SCAN_PORT | (TRUE << pin);
}

void unsetAnalogPIN(unsigned char pin) {
    ANALOG_MODE_PORT = ANALOG_MODE_PORT | (TRUE << pin);
    ANALOG_SCAN_PORT = ANALOG_SCAN_PORT & ~(int) (TRUE << pin);
}

void setAnalogInterrupt(void) {
    clearAnalogInterrupt();
    ANALOG_INTERRUPT_ENABLE = TRUE;
}

void unsetAnalogInterrupt(void) {
    clearAnalogInterrupt();
    ANALOG_INTERRUPT_ENABLE = FALSE;
}

void clearAnalogInterrupt(void) {
    ANALOG_INTERRUPT_OCCURRED = FALSE;
}

void setAutomaticSampling(void) {
    AUTOMATIC_SAMPLING = TRUE;
}

void unsetAutomaticSampling(void) {
    AUTOMATIC_SAMPLING = FALSE;
}

void setAnalogVoltageReference(unsigned char mode) {
    ANALOG_VOLTAGE_REFERENCE = mode;
}

void setAnalogDataOutputFormat(unsigned char adof) {
    ANALOG_DATA_OUTPUT_FORMAT = adof;
}

int getMinimumAnalogClockConversion(void) {
    return (int) ((MINIMUM_TAD_PERIOD * OSC_FREQ_MHZ) / 500.0);
}