/*
 * task100ms.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_SYSTEM_TASKS_TASK100MS_TASK100MS_H_
#define ORKA_SYSTEM_TASKS_TASK100MS_TASK100MS_H_

#include "tasksHelper.h"

extern TaskHandle_t task_100ms;             //!< 100ms task handler

void AE_task100ms(void * param);

#endif /* ORKA_SYSTEM_TASKS_TASK100MS_TASK100MS_H_ */
