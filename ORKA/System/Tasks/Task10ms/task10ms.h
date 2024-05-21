/*
 * task10ms.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_SYSTEM_TASKS_TASK10MS_TASK10MS_H_
#define ORKA_SYSTEM_TASKS_TASK10MS_TASK10MS_H_

#include "tasksHelper.h"

extern TaskHandle_t task_10ms;             //!< 10ms task handler

void AE_task10ms(void * param);


#endif /* ORKA_SYSTEM_TASKS_TASK10MS_TASK10MS_H_ */
