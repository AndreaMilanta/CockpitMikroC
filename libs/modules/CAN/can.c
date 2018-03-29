/**
 * Author: Andrea Milanta
 * Created: 27/03/2018
 *
 * Handles CAN communication
 */

#include "can.h"


// Initialize CAN module
void can_init(uint8_t device, can_masking* mef) 
{
    // Setup BP and Initialization flags
    uint8_t BRP = 1;    
    uint16_t Can_Init_flags = 0;

    switch(OSC_FREQ_MHZ) {    //BRP =  1, 2, 4 se rispettivamente Fck = 20 40 80 MHz
        case 20:
            BRP = 1;
            break;
        case 40:
            BRP = 2;
            break;
        case 80:
            BRP = 4;
            break;
        defualt: 
            BRP = 1;
    }

    Can_Init_flags = _CAN_CONFIG_STD_MSG &             // standard identifier 11 bit
                     _CAN_CONFIG_DBL_BUFFER_ON &       // double buffer mode MODIFICABILE
                     _CAN_CONFIG_MATCH_MSG_TYPE &
                     _CAN_CONFIG_LINE_FILTER_ON &      // wake up by line
                     _CAN_CONFIG_SAMPLE_THRICE &       // for robustness
                     _CAN_CONFIG_PHSEG2_PRG_ON;        // these last two are linked to sync

    // Actual initialization
    switch(device)
    {
    #ifdef CAN1_DEVICE
        case CAN1_DEVICE:
            CAN1Initialize(2, BRP, 3, 4, 2, Can_Init_flags);          // SJW,BRP,PHSEG1,PHSEG2,PROPSEG
            
            // Set masks and filters - Congif mode required
            CAN1SetOperationMode(_CAN_MODE_CONFIG, 0xFF);
            CAN1SetMask(  _CAN_MASK_B1,       mef->b1_mask,      _CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_STD_MSG);
            CAN1SetFilter(_CAN_FILTER_B1_F1,  mef->b1_filter_1,  _CAN_CONFIG_STD_MSG);
            CAN1SetFilter(_CAN_FILTER_B1_F2,  mef->b1_filter_2,  _CAN_CONFIG_STD_MSG);
            CAN1SetMask(  _CAN_MASK_B2,       mef->b2_mask,      _CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_STD_MSG);
            CAN1SetFilter(_CAN_FILTER_B2_F1,  mef->b2_filter_1,  _CAN_CONFIG_STD_MSG);
            CAN1SetOperationMode(_CAN_MODE_NORMAL, 0xFF);
            
            // Enable interrupts
            CAN1_INTERRUPT_ENABLE = TRUE;
            CAN1_INTERRUPT_REC_B0_ENABLE = TRUE;
            CAN1_INTERRUPT_REC_B1_ENABLE = TRUE;

            Delay_ms(250);
            break;
    #endif //CAN1_DEVICE

    #ifdef CAN2_DEVICE
        case CAN2_DEVICE:
            CAN2Initialize(2, BRP, 3, 4, 2, Can_Init_flags);          // SJW,BRP,PHSEG1,PHSEG2,PROPSEG
            
            // Set masks and filters - Congif mode required
            CAN2SetOperationMode(_CAN_MODE_CONFIG, 0xFF);
            CAN2SetMask(  _CAN_MASK_B1,       mef->b1_mask,      _CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_STD_MSG);
            CAN2SetFilter(_CAN_FILTER_B1_F1,  mef->b1_filter_1,  _CAN_CONFIG_STD_MSG);
            CAN2SetFilter(_CAN_FILTER_B1_F2,  mef->b1_filter_2,  _CAN_CONFIG_STD_MSG);
            CAN2SetMask(  _CAN_MASK_B2,       mef->b2_mask,      _CAN_CONFIG_MATCH_MSG_TYPE & _CAN_CONFIG_STD_MSG);
            CAN2SetFilter(_CAN_FILTER_B2_F1,  mef->b2_filter_1,  _CAN_CONFIG_STD_MSG);
            CAN2SetOperationMode(_CAN_MODE_NORMAL, 0xFF);
            
            // Enable interrupts
            CAN2_INTERRUPT_ENABLE = TRUE;
            CAN2_INTERRUPT_REC_B0_ENABLE = TRUE;
            CAN2_INTERRUPT_REC_B1_ENABLE = TRUE;

            Delay_ms(250);
            break;
    #endif //CAN1_DEVICE
    }
}


// dataBuffer must be of size 8
uint8_t can_write(uint8_t device, uint32_t id, uint8_t dataBuffer[], uint16_t priority) 
{
    uint8_t sent, i = 0;
    do {
        switch (device)
        {
        #ifdef CAN1_DEVICE
            case CAN1_DEVICE:
                sent = CAN1Write(id, dataBuffer, CAN_PACKET_SIZE, CAN_DEFAULT_FLAGS & priority);
                i += 1;
                break;
        #endif //CAN1_DEVICE

        #ifdef CAN2_DEVICE
            case CAN2_DEVICE:
                sent = CAN2Write(id, dataBuffer, CAN_PACKET_SIZE, CAN_DEFAULT_FLAGS & priority);
                i += 1;
                break;
        #endif //CAN2_DEVICE

            defualt:
                return ERROR;
        }
    } while ((sent == 0) && (i < CAN_RETRY_LIMIT));
    if (i == CAN_RETRY_LIMIT) 
        return ERROR;
    return i;
}


#ifdef CAN1_DEVICE
    void can1_read(uint32_t *id, uint8_t dataBuffer[], uint16_t *dataLength, uint16_t *inFlags) 
    {
        if (CAN1_INTERRUPT_ONB0_OCCURRED) 
        {
            CAN1_INTERRUPT_ONB0_OCCURRED = FALSE;
            Can1Read(id, dataBuffer, dataLength, inFlags);
        }
        else if (CAN1_INTERRUPT_ONB1_OCCURRED) 
        {
            CAN1_INTERRUPT_ONB1_OCCURRED = FALSE;
            Can1Read(id, dataBuffer, dataLength, inFlags);
        }
    }
#endif //CAN1_DEVICE

#ifdef CAN2_DEVICE
    void can2_read(uint32_t *id, uint8_t dataBuffer[], uint16_t *dataLength, uint16_t *inFlags) 
    {
        if (CAN2_INTERRUPT_ONB0_OCCURRED) 
        {
            CAN2_INTERRUPT_ONB0_OCCURRED = FALSE;
            Can2Read(id, dataBuffer, dataLength, inFlags);
        }
        else if (CAN2_INTERRUPT_ONB1_OCCURRED) 
        {
            CAN2_INTERRUPT_ONB1_OCCURRED = FALSE;
            Can2Read(id, dataBuffer, dataLength, inFlags);
        }
    }
#endif //CAN2_DEVICE
