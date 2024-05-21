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
        if(crcBuffer.dataFlag)
        {
            AE_soxCalculate_UML(&batSox, crcBuffer.rxCurrent, crcBuffer.rxVoltage);
            crcBuffer.dataFlag = 0;

            counterOf10msTask++;
        }
        vTaskDelay(10);
    }
}
