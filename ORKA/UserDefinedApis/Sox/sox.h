/*
 * sox.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef SOX_SOX_H_
#define SOX_SOX_H_

#include "stdint.h"

#define ABSOLUTE(x)                     (((x) < 0)? -(x) : (x))
#define SOH_CALCULATE_PERIOD            (1000)      //if total capacity differense is bigger than 1000mA calculate SOH

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
    BAT_NO_OPERATION
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
    float batNetCapacity;                // !!!calculated by program do not set
    float batDodCapacity;                   // !!!calculated by program do not set
    float batMinDodCapacity;                // !!!calculated by program do not set
    float batMaxDodCapacity;                // !!!calculated by program do not set
}SoxInitTypeDef_ts;

/**
 * Battery Instantaneous Datas
 */
typedef struct BatSoxVal_s{
    double soc;                             //!< ratio between 0-100
    double soh;                             //!< ratio between 0-100
    double calibrationSoh;                  //!< (calculated system calibration capacity) / (4500.0f)
    double cycle;                           //!< cell life cycle counter
    double batInstantaneousCapacity;        //!< TODO may be located in SoxInitTypeDef_ts structure
    double previousCapacity;                //!< use to calculate the soh calculation period
    double sumOfCapacityChange;             //!< sum the changes changes ratio to calculate soh
    double batTotalCapacity;                //!< system calculated capacity by fully charging and discharging or fully discharging or charging
    BatState_te batStates;                  //!<
    BatState_te batCalibrationState;        //!<
}BatSoxVal_ts;


void AE_soxInit(SoxInitTypeDef_ts * soxInit);
void AE_soxCalculate_UML(BatSoxVal_ts * batSox, float passingCurrent, float meanCellVolt);
BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void);

#endif /* SOX_SOX_H_ */
