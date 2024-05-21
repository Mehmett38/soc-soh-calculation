/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "circularBuff.h"
#include "FreeRTOS.h"
#include "os_task.h"
#include "soc.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

#define UNUSED(x)   ((void)x)
uint8_t toggle = 1;
uint8_t returnVarningClose;

void delay(uint32_t time)
{
    time *= 11520;          //needed to wait 1ms delay
    while(time--);
}

uint8_t rxData;
float socCurrent;

TaskHandle_t task_10ms;             //!< 10ms task handler
TaskHandle_t task_100ms;            //!< 100ms task handler

void OsTask_10ms(void * param);
void OsTask_100ms(void * param);

uint32_t itNumber;
uint32_t packetNumber;
uint32_t processNumber;

uint32_t taskProcessNum;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
//    ltcInit(spiREG3);

    sciInit();
    AE_socInitialize();

    _enable_interrupt_();
    sciEnableNotification(scilinREG, SCI_RX_INT);

    sciReceive(scilinREG, 1, &rxData);

    BaseType_t status;
    //!< 10ms task
    status = xTaskCreate(OsTask_10ms, "task_10ms", (configMINIMAL_STACK_SIZE * 3),
                         NULL, 2, &task_10ms);
    if(status != pdPASS)
    {
        vTaskDelete(task_10ms);
    }
    //!< 100ms task
    status = xTaskCreate(OsTask_100ms, "task_100ms", (configMINIMAL_STACK_SIZE * 3),
                         NULL, 2, &task_100ms);
    if(status != pdPASS)
    {
        vTaskDelete(task_100ms);
    }

    vTaskStartScheduler();

/* USER CODE END */

}


/* USER CODE BEGIN (4) */

void OsTask_10ms(void * param)
{
    for(;;)
    {
        if(crcBuffer.dataFlag)
        {
            AE_calculateSoc();
            crcBuffer.dataFlag = 0;
//            taskProcessNum++;
        }
        vTaskDelay(10);
    }
}

void OsTask_100ms(void * param)
{
    for(;;)
    {
        vTaskDelay(100);
    }
}

void sciNotification(sciBASE_t *sci, uint32 flags)
{
    if(sci == scilinREG && flags == SCI_RX_INT)
    {
        itNumber++;
        sciReceive(scilinREG, 1, &rxData);
        crcBuffer.buffer[crcBuffer.head++] = rxData;
        crcBuffer.head %= BUFFER_LEN;

        if(rxData == '\n')
        {
            packetNumber++;
            processNumber++;

            if(crcBuffer.buffer[(crcBuffer.tail + 4) % BUFFER_LEN] != '\r')
            {
                processNumber--;
                return;
            }

            AE_circularBufferParse();
        }
    }
}
/* USER CODE END */
