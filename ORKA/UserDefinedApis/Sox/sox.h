/*
 * sox.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef SOX_SOX_H_
#define SOX_SOX_H_

#include "stdint.h"


typedef enum BatState_e{
    BAT_NOT_INITIALIZED,
    BAT_INITIALIZED,
    BAT_UPPER_DOD_POINT,
    BAT_LOWER_DOD_POINT,
    BAT_CHARGING_MODE,
    BAT_DISCHARGING_MODE,
    BAT_IDLE_MODE
}BatState_te;

/**
 * Battery specifications
 */
typedef struct SoxInitTypeDef_s{
    uint32_t cellCapacityInmAh;             //capacity of one cell
    uint16_t numberOfParallelCell;
    uint16_t numberOfLifeCycle;             //cell max cycle number or desired number
    uint16_t cellLowerDocRatio;             //Doc = 1 - DOD between 0-100
    uint16_t cellUpperDocRatio;             //Doc = 1 - DOD between 0-100
    float minDischargeVoltage;              // !!!calculated by program do not set
    float maxChargeVoltage;                 // !!!calculated by program do not set
    float batTotatlCapacity;                // !!!calculated by program do not set
    float batDodCapacity;                   // !!!calculated by program do not set
}SoxInitTypeDef_ts;

/**
 * Battery Instantaneous Datas
 */
typedef struct BatSoxVal_s{
    float soc;
    float soh;                              //ratio beetween 0-100
    float cycle;
    float batInstantaneousCapacity;
    BatState_te batStates;
}BatSoxVal_ts;


void AE_soxInit(SoxInitTypeDef_ts * soxInit);
void AE_soxCalculate_UML(BatSoxVal_ts * batSox, float passingCurrent, float meanCellVolt);


#endif /* SOX_SOX_H_ */
