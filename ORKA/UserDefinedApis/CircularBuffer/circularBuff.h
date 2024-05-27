/*
 * circularBuff.h
 *
 *  Created on: 26 �ub 2024
 *      Author: mehmet.dincer
 */

#ifndef CIRCULAR_BUFFER_CIRCULARBUFF_H_
#define CIRCULAR_BUFFER_CIRCULARBUFF_H_

#include "sci.h"
#include "sys_core.h"

#define BUFFER_LEN              (45)

typedef struct{
    uint8_t buffer[BUFFER_LEN];
    uint16_t head;
    uint16_t tail;
    float rxCurrent;
    float rxVoltage;
    uint32_t receivedDataNumber;
    uint8_t isDataReadyFlag;
}CircularBuffer;
extern CircularBuffer crcBuffer;

void AE_circularBufferParse();

#endif /* CIRCULAR_BUFFER_CIRCULARBUFF_H_ */
