/*
 * task100ms.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include "tasksHelper.h"

TaskHandle_t task_100ms;             //!< 10ms task handler


void AE_task100ms(void * param)
{
    for(;;)
    {
        vTaskDelay(100);
    }
}
