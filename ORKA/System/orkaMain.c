/*
 * orkaMain.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include "orkaMain.h"
#include "math.h"

static void orkaHarwareInit();
static void orkaSoxInit();

extern uint8_t rxData;          //!< sciLinReg2 read val
extern BatSoxVal_ts batSox;

int AE_orkaMain()
{
    BaseType_t status;

    orkaHarwareInit();
    orkaSoxInit();

    /*<<<<<<<<<<<<<<<<<<<<<<<<<<<<-Task Creation->>>>>>>>>>>>>>>>>>>>>>>>>>>>*/
    //!< 10ms task
    status = xTaskCreate(AE_task10ms,
                         "task_10ms",
                         (configMINIMAL_STACK_SIZE * 3),
                         NULL,
                         TASK_HIGh_PRIORITY,
                         &task_10ms);
    configASSERT(status);

    //!< 100ms task
    status = xTaskCreate(AE_task100ms,
                         "task_100ms",
                         (configMINIMAL_STACK_SIZE * 3),
                         NULL,
                         TASK_MIDDLE_PRIORITY,
                         &task_100ms);
    configASSERT(status);

    vTaskStartScheduler();

    return 0;
}

/**
 * @initialize the periperal that used in the project
 * @return none
 */
static void orkaHarwareInit()
{
    //enable sciLin to receive instantaneous current information
    sciInit();

    //enable sciLin receive interrupt
    sciEnableNotification(scilinREG, SCI_RX_INT);

    //enable gioB1 to blink when the new current inf come
    gioInit();

    //enable the interrupts
    _enable_interrupt_();

    sciReceive(scilinREG, 1, &rxData);
    crcBuffer.rxVoltage = 3.5f;     //dumy variable
}

/**
 * @brief initialize the sox with the battary specifications
 */
static void orkaSoxInit()
{
    SoxInitTypeDef_ts soxInit = {0};

    soxInit.cellCapacityInmAh       = 4500u;
    soxInit.numberOfParallelCell    = 1u;
    soxInit.numberOfLifeCycle       = 600u;         //             __________________________________
    soxInit.cellLowerDocRatio       = 0u;           //system DOD  | Lower | System Operation | Upper |
    soxInit.cellUpperDocRatio       = 0u;           //            |__DOC__|______DOD_________|__DOC__|

    AE_soxInit(&soxInit);
}

