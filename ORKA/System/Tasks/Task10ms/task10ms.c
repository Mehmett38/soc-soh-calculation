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
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount ();

    for(;;)
    {
        if(crcBuffer.isDataReadyFlag != 0)
        {
            AE_soxCalculate_UML(&batSox, crcBuffer.rxCurrent, crcBuffer.rxVoltage);

            crcBuffer.isDataReadyFlag = 0;
        }

        counterOf10msTask++;
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}
