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
        crcBuffer.buffer[crcBuffer.head] = rxData;
        crcBuffer.head = (crcBuffer.head + 1) % BUFFER_LEN;


        if(rxData == '\n')
        {
            if(crcBuffer.head == 0)
            {
                if(crcBuffer.buffer[BUFFER_LEN - 2] != '\r')
                    return;
            }
            else if(crcBuffer.head == 1)
            {
                if(crcBuffer.buffer[BUFFER_LEN - 1] != '\r')
                    return;
            }
            else
            {
                if(crcBuffer.buffer[crcBuffer.head - 2] != '\r')
                    return;
            }

            AE_circularBufferParse();
        }
    }
}



