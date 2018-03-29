/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * Handles CAN communication
 */

/** Come usare la libreria CAN
 *
 * Per mandare interi
 * > Can_writeInt(indirizzo, valore);
 *
 * Per mandare byte
 * > Can_writeByte(indirizzo, valore);
 *
 * Per mandare pacchetti (esempio int + byte)
 * > Can_resetWritePacket();
 * > Can_addIntToWritePacket(valore);
 * > Can_addByteToWritePacket(valore);
 * > Can_write(indirizzo);
 */
 
 
#ifndef CAN_H
#define CAN_H

#include "basic.h"
#include "current.h"

#define CAN_RETRY_LIMIT 5 //50
#define CAN_DEFAULT_FLAGS _CAN_TX_STD_FRAME & _CAN_TX_NO_RTR_FRAME

#ifdef CAN1_DEVICE
    #define onCan1Interrupt void CAN1_Interrupt() iv IVT_ADDR_C1INTERRUPT
    #define can1_clearInterrupt() CAN1_INTERRUPT_OCCURRED = FALSE
#endif // CAN1_DEVICE

#ifdef CAN2_DEVICE
    #define onCan2Interrupt void CAN2_Interrupt() iv IVT_ADDR_C2INTERRUPT
    #define can2_clearInterrupt() CAN2_INTERRUPT_OCCURRED = FALSE
#endif // CAN2_DEVICE

#define CAN_PRIORITY_HIGH _CAN_TX_PRIORITY_0
#define CAN_PRIORITY_MEDIUM _CAN_TX_PRIORITY_1
#define CAN_PRIORITY_LOW _CAN_TX_PRIORITY_2
#define CAN_PRIORITY_VERYLOW _CAN_TX_PRIORITY_3

#define CAN_PACKET_SIZE 8

// From silicon errdata: avoiding interrupts on certain can settings and values assignments
#define DISABLE_IT asm DISI #0X3FF

#define SET_CPU_IPL(ipl){ \
    int DISI_save; \
    \
    DISI_save = DISICNT; \
    DISABLE_IT;\
    SRbits.IPL = ipl; \
    asm {nop}; \
    asm {nop}; \
    DISICNT = DISI_save; } (void) 0;

#define SET_AND_SAVE_CPU_IPL(save_to, ipl){ \
    save_to = SRbits.IPL; \
    SET_CPU_IPL(ipl); } (void) 0;

#define RESTORE_CPU_IPL(saved_to) SET_CPU_IPL(saved_to)
/*
#define INTERRUPT_PROTECT(x) { \
int save_sr; \
SET_AND_SAVE_CPU_IPL(save_sr, 7);\
x; \
RESTORE_CPU_IPL(save_sr); } (void) 0;
//*/
//>


// Struct that holds masking and filtering info 
typedef struct {
    uint16_t b1_mask;
    uint16_t b1_filter_1;
    uint16_t b1_filter_2;
    uint16_t b2_mask;
    uint16_t b2_filter_1;
} can_masking;


void can_init(uint8_t device, can_masking* mef);

uint8_t can_write(uint8_t device, uint32_t id, uint8_t dataBuffer[], uint16_t priority);

#ifdef CAN1_DEVICE
    void can1_read(uint32_t *id, uint8_t dataBuffer[], uint16_t *dataLength, uint16_t *inFlags);
#endif //CAN1_DEVICE

#ifdef CAN2_DEVICE
    void can2_read(uint32_t *id, uint8_t dataBuffer[], uint16_t *dataLength, uint16_t *inFlags);
#endif //CAN2_DEVICE

#endif //CAN_H