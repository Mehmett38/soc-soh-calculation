/*
 * circularBuff.h
 *
 *  Created on: 26 Þub 2024
 *      Author: mehmet.dincer
 */

#ifndef CIRCULAR_BUFFER_CIRCULARBUFF_H_
#define CIRCULAR_BUFFER_CIRCULARBUFF_H_

#include "sci.h"
#include "sys_core.h"

#define BUFFER_LEN              (20)

typedef struct{
    uint8_t buffer[BUFFER_LEN];
    uint16_t head;
    uint16_t tail;
    float rxCurrent;
    uint8_t dataFlag;
}CircularBuffer;
extern CircularBuffer crcBuffer;

void AE_circularBufferParse();

#endif /* CIRCULAR_BUFFER_CIRCULARBUFF_H_ */
