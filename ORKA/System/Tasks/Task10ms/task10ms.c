/*
 * task10ms.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include "tasksHelper.h"

TaskHandle_t task_10ms;             //!< 10ms task handler

uint32_t counterOf10msTask = 0;

void AE_task10ms(void * param)
{
    for(;;)
    {
        if(crcBuffer.dataFlag != 0)
        {
            crcBuffer.dataFlag = 0;
        }
        else
        {
            crcBuffer.rxCurrent = 0;
        }

        AE_soxCalculate_UML(&batSox, crcBuffer.rxCurrent, crcBuffer.rxVoltage);

        counterOf10msTask++;

        vTaskDelay(10);
    }
}
