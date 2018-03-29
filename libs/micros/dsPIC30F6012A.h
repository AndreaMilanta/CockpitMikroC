/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * holds definitions and main setup functions for the dsPIC30F6012A microcontroller
 */

#ifndef DSPIC30F6012A_H
#define DSPIC30F6012A_H

#include "basic.h"

 #define OSC_FREQ_MHZ 80

 // General defines
 #define MAX_ANALOG_CLOCK_CONVERSION_VALUE   32
 #define MINIMUM_TAD_PERIOD 154 //Nanoseconds
 #define MINIMUM_CONVERSION_TAD_COUNT    13 //Minimum conversion period
 #define MAXIMUM_CONVERSION_TAD_COUNT    43 //Maximum conversion period

 // Devices list
 #define TIMER1_DEVICE 1
 #define TIMER2_DEVICE 2
 #define TIMER4_DEVICE 3
 #define INT0_DEVICE 4
 #define INT1_DEVICE 5
 #define INT2_DEVICE 6
 #define INT4_DEVICE 8

 // Analog Pin Inputs
 #define AN0  0
 #define AN1  1
 #define AN2  2
 #define AN3  3
 #define AN4  4
 #define AN5  5
 #define AN6  6
 #define AN7  7
 #define AN8  8
 #define AN9  9
 #define AN10  10
 #define AN11  11
 #define AN12  12
 #define AN13  13
 #define AN14  14
 #define AN15  16

 // External pin interrupt
 #define INT0_TRIGGER_EDGE   INTCON2.INT0EP
 #define INT1_TRIGGER_EDGE   INTCON2.INT1EP
 #define INT2_TRIGGER_EDGE   INTCON2.INT2EP
 #define INT4_TRIGGER_EDGE   INTCON2.INT4EP  */
 #define INT0_PRIORITY   IPC0bits.INT0IP
 #define INT1_PRIORITY   IPC4bits.INT1IP
 #define INT2_PRIORITY   IPC5bits.INT2IP
 #define INT4_PRIORITY   IPC9bits.INT4IP
 #define INT0_OCCURRED   IFS0.INT0IF
 #define INT1_OCCURRED    IFS1.INT1IF
 #define INT2_OCCURRED   IFS1.INT2IF
 #define INT4_OCCURRED   IFS2.INT4IF
 #define INT0_ENABLE IEC0.INT0IE
 #define INT1_ENABLE IEC1.INT1IE
 #define INT2_ENABLE IEC1.INT2IE
 #define INT4_ENABLE IEC2.INT4IE

 // Timer (Implemented: 1 ~ 2 ~ 4)
 #define TIMER1_PRESCALER    T1CONbits.TCKPS
 #define TIMER1_PERIOD   PR1
 #define TIMER1_PRIORITY IPC0bits.T1IP
 #define TIMER1_ENABLE_INTERRUPT IEC0bits.T1IE
 #define TIMER1_ENABLE   T1CONbits.TON
 #define TIMER1_OCCURRED IFS0bits.T1IF

 #define TIMER2_PRESCALER    T2CONbits.TCKPS
 #define TIMER2_PERIOD   PR2
 #define TIMER2_PRIORITY IPC1bits.T2IP
 #define TIMER2_ENABLE_INTERRUPT IEC0bits.T2IE
 #define TIMER2_ENABLE   T2CONbits.TON
 #define TIMER2_OCCURRED IFS0bits.T2IF

 #define TIMER4_PRESCALER    T4CONbits.TCKPS
 #define TIMER4_PERIOD   PR4
 #define TIMER4_PRIORITY IPC5bits.T4IP
 #define TIMER4_ENABLE_INTERRUPT IEC1bits.T4IE
 #define TIMER4_ENABLE   T4CONbits.TON
 #define TIMER4_OCCURRED IFS1bits.T4IF

 // Analog
 #define ANALOG_INTERRUPT_ENABLE IEC0bits.ADIE
 #define ANALOG_INTERRUPT_OCCURRED   IFS0bits.ADIF
 #define ANALOG_SAMPLING_ENABLE   ADCON1bits.ADON
 #define ANALOG_SAMPLING_STATUS ADCON1bits.SAMP
 #define ANALOG_IS_NOT_BUSY ADCON1bits.DONE
 #define AUTOMATIC_SAMPLING  ADCON1bits.ASAM
 #define ANALOG_CONVERSION_TRIGGER_SOURCE    ADCON1bits.SSRC
 #define ANALOG_DATA_OUTPUT_FORMAT   ADCON1bits.FORM
 #define ANALOG_IDLE_ENABLE  ADCON1bits.ADSIDL
 #define ANALOG_VOLTAGE_REFERENCE    ADCON2bits.VCFG
 #define ANALOG_CH0_SCAN_ENABLE  ADCON2bits.CSCNA
 #define INTERRUPT_ON_SAMPLINGS_COMPLETION_COUNT ADCON2bits.SMPI
 #define ANALOG_BUFFER_SIZE  ADCON2bits.BUFM
 #define ANALOG_ENABLE_ALTERNATING_MULTIPLEXER ADCON2bits.ALTS
 #define ANALOG_AUTOMATIC_SAMPLING_TADS_INTERVAL ADCON3bits.SAMC
 #define ANALOG_CLOCK_SOURCE ADCON3bits.ADRC
 #define ANALOG_CLOCK_CONVERSION ADCON3bits.ADCS
 #define ANALOG_CHANNEL_B_NEGATIVE_INPUT ADCHSbits.CH0NB
 #define ANALOG_CHANNEL_B_POSITIVE_INPUT ADCHSbits.CH0SB
 #define ANALOG_CHANNEL_A_NEGATIVE_INPUT ADCHSbits.CH0NA
 #define ANALOG_CHANNEL_A_POSITIVE_INPUT ADCHSbits.CH0SA
 #define ANALOG_MODE_PORT    ADPCFG
 #define ANALOG_SCAN_PORT    ADCSSL
 #define ANALOG_BUFFER0  ADCBUF0

 // Analog Conversion Trigger Sources
 #define ACTS_AUTOMATIC  7
 #define ACTS_MOTOR_PWM_END  3
 #define ACTS_TIMER3 2
 #define ACTS_INT0   1
 #define ACTS_SAMPLING_ENABLE_BIT    0
 // Analog Data Output Format
 #define ADOF_SIGNED_FRACTIONAL   3
 #define ADOF_UNSIGNED_FRACTIONAL 2
 #define ADOF_SIGNED_INTEGER  1
 #define ADOF_UNSIGNED_INTEGER    0
 // Analog Voltage Reference
 #define AVR_AVDD_AVSS   0
 #define AVR_VREF_AVSS   1
 #define AVR_AVDD_VREF   2
 #define AVR_VREF_VREF   3
 // Analog Buffer Size
 #define ABS_SPLITTED_8BIT   1
 #define ABS_16BIT   0
 // Analog Clock Source
 #define ACS_INTERNAL_RC 1
 #define ACS_EXTERNAL    0
 //Analog Channel Negative Input
 #define ACNI_AN1    1
 #define ACNI_VREF   0

 // Interrupt handlers
 #define onTimer1Interrupt void timer1_interrupt() iv IVT_ADDR_T1INTERRUPT ics ICS_AUTO
 #define onTimer2Interrupt void timer2_interrupt() iv IVT_ADDR_T2INTERRUPT ics ICS_AUTO
 #define onTimer4Interrupt void timer4_interrupt() iv IVT_ADDR_T4INTERRUPT ics ICS_AUTO
 #define onExternal0Interrupt void external0() iv IVT_ADDR_INT0INTERRUPT ics ICS_AUTO
 #define onExternal1Interrupt void external1() iv IVT_ADDR_INT1INTERRUPT ics ICS_AUTO
 #define onExternal2Interrupt void external2() iv IVT_ADDR_INT2INTERRUPT ics ICS_AUTO
 #define onExternal4Interrupt void external4() iv IVT_ADDR_INT4INTERRUPT ics ICS_AUTO
 #define onADCInterrupt void analog_interrupt() iv IVT_ADDR_ADCINTERRUPT ics ICS_AUTO

 // Faster timer operations
 #define clearTimer1() TIMER1_OCCURRED = FALSE
 #define clearTimer2() TIMER2_OCCURRED = FALSE
 #define clearTimer4() TIMER4_OCCURRED = FALSE
 #define turnOnTimer4() TIMER4_ENABLE = TRUE
 #define turnOffTimer4() TIMER4_ENABLE = FALSE

 /* Actually declared in dsPIC30F4012.c file
 const double INSTRUCTION_PERIOD = 4.0 / OSC_FREQ_MHZ;
 const unsigned int PRESCALER_VALUES[] = {1, 8, 64, 256};
 //*/

 // Initialization
 void setAllPinAsDigital(void);

 // External Interrupts
 void setInterruptPriority(unsigned char device, unsigned char priority);
 void setExternalInterrupt(unsigned char device, char edge);
 void switchExternalInterruptEdge(unsigned char);
 char getExternalInterruptEdge(unsigned char);
 void clearExternalInterrupt(unsigned char);

 // Timers
 void setTimer(unsigned char device, double timePeriod);
 void clearTimer(unsigned char device);
 void turnOnTimer(unsigned char device);
 void turnOffTimer(unsigned char device);
 unsigned int getTimerPeriod(double timePeriod, unsigned char prescalerIndex);
 unsigned char getTimerPrescaler(double timePeriod);
 double getExactTimerPrescaler(double timePeriod);

 // Analog
 void setupAnalogSampling(void);
 void turnOnAnalogModule();
 void turnOffAnalogModule();
 void startSampling(void);
 unsigned int getAnalogValue(void);
 void setAnalogPIN(unsigned char pin);
 void unsetAnalogPIN(unsigned char pin);
 void setAnalogInterrupt(void);
 void unsetAnalogInterrupt(void);
 void clearAnalogInterrupt(void);

 // Sampling
 void setAutomaticSampling(void);       //will samples continuously
 void unsetAutomaticSampling(void);

 // See defines @Analog Voltage Reference
 void setAnalogVoltageReference(unsigned char mode);
 void setAnalogDataOutputFormat(unsigned char adof);
 int getMinimumAnalogClockConversion(void);

#endif //DSPIC30F6012A_H