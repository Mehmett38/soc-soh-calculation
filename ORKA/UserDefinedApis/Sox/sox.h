/*
 * sox.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef SOX_SOX_H_
#define SOX_SOX_H_

#include "stdint.h"
#include "cells.h"
#include "math.h"

#define SOH_CALCULATE_PERIOD            (MAX_CELL_CAPACITY * soxInitVals.numberOfParallelCell / 2)      //if total capacity differense is bigger than 1000mA calculate SOH
#define SYSTEM_TOTAL_CAPACITY           (MAX_CELL_CAPACITY * soxInitVals.numberOfParallelCell)

//!<@refgroup DOD_LEVEL
#define LOWER_DOD_LEVEL                 (0u)
#define UPPER_DOD_LEVEL                 (1u)

typedef enum BatState_e{
    BAT_NOT_INITIALIZED,                    //!!! do not change the order, 0.
    BAT_INITIALIZED_WITHOUT_CALIBRATION,    //!!! do not change the order, 2.
    BAT_INITIALIZED,                        //!!! do not change the order, 4.
    BAT_CALIBRATED,
    BAT_WAIT_FOR_LOWER_DOD_POINT,
    BAT_WAIT_FOR_UPPER_DOD_POINT,
    BAT_UPPER_DOD_POINT,
    BAT_LOWER_DOD_POINT,
    BAT_CHARGING_MODE,
    BAT_DISCHARGING_MODE,
    BAT_IDLE_MODE,
}BatState_te;

/**
 * Battery specifications
 */
typedef struct SoxInitTypeDef_s{
    uint32_t cellCapacityInmAh;             //capacity of one cell
    uint16_t numberOfParallelCell;          //used for the total capacity calculation
    uint16_t numberOfSerialCell;
    uint16_t numberOfLifeCycle;             //cell max cycle number or desired number
    float cellLowerDocRatio;                //Doc = 1 - DOD between 0-100
    float cellUpperDocRatio;                //Doc = 1 - DOD between 0-100
    float dodRatio;                         // dod ratio between 0-1
    float minDischargeVoltage;              // !!!calculated by program do not set
    float maxChargeVoltage;                 // !!!calculated by program do not set
    float batNetCapacity;                   // !!!calculated by program do not set
    float batDodCapacity;                   // !!!calculated by program do not set
    float batMinDodCapacity;                // !!!calculated by program do not set
    float batMaxDodCapacity;                // !!!calculated by program do not set
    float batTempMaxDodCapacity;
}SoxInitTypeDef_ts;

/**
 * Battery Instantaneous Datas
 */
typedef struct BatSoxVal_s{
    float soc;                             //!< ratio between 0-100
    float soh;                             //!< ratio between 0-100
    float calibrationSoh;                  //!< (system calculated calibration capacity) / (4500.0f) used to set soh between 0-1
    float cycle;                           //!< cell life cycle counter
    float batInstantaneousCapacity;        //!<
    float previousCapacity;                //!< use to calculate the soh calculation period
    float sumOfCapacityChange;             //!< sum the changes changes ratio to calculate soh
    float batTotalCapacity;                //!< system calculated capacity by fully charging and discharging or fully discharging or charging
    BatState_te batStates;                  //!<
    BatState_te batCalibrationState;        //!<
}BatSoxVal_ts;


void AE_soxInit(SoxInitTypeDef_ts * soxInit);
void AE_soxCalculate_UML(BatSoxVal_ts * batSox, float passingCurrent, float systemTotalVolt);
BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void);
void AE_dodCalibrate();

#endif /* SOX_SOX_H_ */
