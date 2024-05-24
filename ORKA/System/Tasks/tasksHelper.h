/*
 * tasksHelper.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_SYSTEM_TASKS_TASKSHELPER_H_
#define ORKA_SYSTEM_TASKS_TASKSHELPER_H_

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "circularBuff.h"
#include "sox.h"

typedef enum RtosPriorities_e
{
    TASK_IDLE,
    TASK_LOW_PRIOTIY,
    TASK_MIDDLE_PRIORITY,
    TASK_HIGh_PRIORITY,
    TASK_REAL_TIME
}RtosPriorities_te;

extern BatSoxVal_ts batSox;

#endif /* ORKA_SYSTEM_TASKS_TASKSHELPER_H_ */
