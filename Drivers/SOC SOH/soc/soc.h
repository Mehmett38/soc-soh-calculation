/*
 * soc.h
 *
 *  Created on: 26 Þub 2024
 *      Author: mehmet.dincer
 */

#ifndef SOC_SOH_SOC_SOC_H_
#define SOC_SOH_SOC_SOC_H_

#include "stdint.h"
#include "molicel.h"
#include "stdbool.h"
#include "circularBuff.h"

typedef struct{
    float batteryCapacity;
    float voltage;
    float socRatio;
    float soh;
    float totalCurrent;
    float cycle;
}SocState;

void AE_socInitialize();
void AE_calculateSoc();


#endif /* SOC_SOH_SOC_SOC_H_ */
