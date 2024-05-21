/*
 * Notification.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include "sci.h"
#include "circularBuff.h"

uint8_t rxData;

void sciNotification(sciBASE_t *sci, uint32 flags)
{
    if(sci == scilinREG && flags == SCI_RX_INT)
    {
        sciReceive(scilinREG, 1, &rxData);
        crcBuffer.buffer[crcBuffer.head++] = rxData;
        crcBuffer.head %= BUFFER_LEN;

        if(rxData == '\n')
        {
            if(crcBuffer.buffer[(crcBuffer.tail + 8) % BUFFER_LEN] != '\r')
            {
                return;
            }

            AE_circularBufferParse();
        }
    }
}



