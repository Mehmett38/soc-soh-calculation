/*
 * circularBuffer.c
 *
 *  Created on: 26 Þub 2024
 *      Author: mehmet.dincer
 */

#include "circularBuff.h"

CircularBuffer crcBuffer;

void AE_circularBufferParse()
{
    uint8_t rxBuffer[4];
    uint8_t i;

    for(i = 0; i < 4; i++)
    {
        rxBuffer[i] = crcBuffer.buffer[crcBuffer.tail++];
        crcBuffer.tail %= BUFFER_LEN;
    }

    crcBuffer.tail = crcBuffer.head;
    crcBuffer.rxCurrent = *((float*)((void*)rxBuffer));
    crcBuffer.dataFlag = 1;
}
