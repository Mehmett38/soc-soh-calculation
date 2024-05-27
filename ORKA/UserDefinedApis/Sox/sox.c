/*
 * sox.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include <CellLookUpTable/cellLookupTable.h>
#include "sox.h"

BatSoxVal_ts batSox;

static SoxInitTypeDef_ts soxInitVals;
static BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void);

/**
 * @brief
 * @param[in]
 * @return none
 */
void AE_soxInit(SoxInitTypeDef_ts * soxInit)
{
    //copy battery information
    soxInitVals = *soxInit;

    //read the sox information from the eeprom NOTE this is dummy function
    batSox = AE_readBatSoxDatasFromEeprom();

    //calculate the system capacity
    uint32_t cellCapacityInmAh     = soxInitVals.cellCapacityInmAh;
    uint16_t numberOfParallelCell  = soxInitVals.numberOfParallelCell;
    uint16_t dod = 100 - soxInitVals.cellLowerDocRatio - soxInitVals.cellUpperDocRatio;

    soxInitVals.batTotatlCapacity = cellCapacityInmAh * numberOfParallelCell * (batSox.soh / 100.0f);
    soxInitVals.batDodCapacity    = soxInitVals.batTotatlCapacity * (dod / 100.0f);

    //calculate the minimum and maximum voltage according to dod
    float batCapacity = soxInitVals.batTotatlCapacity;
    uint32_t dodLowerCapacity = (batCapacity * soxInitVals.cellLowerDocRatio) / 100.0f;
    uint32_t dodUpperCapacity = (batCapacity * (100 - soxInitVals.cellUpperDocRatio)) / 100.0f;

    //calculate the min and max voltage according to DOD
    CellTable_ts moliTab = {0};
    moliTab = AE_tableFindByCapacity(dodLowerCapacity, CELL_TABLE_DISCHARGING);
    soxInitVals.minDischargeVoltage = moliTab.voltage;

    moliTab = AE_tableFindByCapacity(dodUpperCapacity, CELL_TABLE_CHARGING);
    soxInitVals.maxChargeVoltage = moliTab.voltage;
}

/**
 * @brief calculate the soc and soh
 * @param[in] batSox states global variable
 * @param[in] instantaneous passing current
 * @param[in] meaning cell voltage of the cell in the battery
 * @none
 */
void AE_soxCalculate_UML(BatSoxVal_ts * batSox, float passingCurrent, float meanCellVolt)
{

    //!< first swithc check the system is initialized and calibrated
    switch(batSox->batStates)
    {
        case BAT_NOT_INITIALIZED ... BAT_INITIALIZED_WITHOUT_CALIBRATION:       //work only one after this time read from the eeprom
        {
            if(meanCellVolt >= soxInitVals.maxChargeVoltage)
            {
                batSox->batStates = BAT_UPPER_DOD_POINT;
            }
            else if(meanCellVolt <= soxInitVals.minDischargeVoltage)
            {
                batSox->batStates = BAT_LOWER_DOD_POINT;
            }
            else
            {
                batSox->batStates = (batSox->batCalibrationState != BAT_NOT_INITIALIZED) ? BAT_INITIALIZED_WITHOUT_CALIBRATION : batSox->batStates;
            }
            break;
        }
        case BAT_UPPER_DOD_POINT:       //enter only one times
        {
            batSox->soc = 100.0f;
            batSox->batInstantaneousCapacity = 0;

            batSox->batCalibrationState = (batSox->batCalibrationState == BAT_WAIT_FOR_UPPER_DOD_POINT) ? BAT_CALIBRATED : BAT_WAIT_FOR_LOWER_DOD_POINT;
            batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED)? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

            break;
        }
        case BAT_LOWER_DOD_POINT:       //enter only one times
        {
            batSox->soc = 0.0f;
            batSox->batInstantaneousCapacity = 0;

            batSox->batCalibrationState = (batSox->batCalibrationState == BAT_WAIT_FOR_LOWER_DOD_POINT) ? BAT_CALIBRATED : BAT_WAIT_FOR_UPPER_DOD_POINT;
            batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED)? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

            break;
        }
    }

    //!< second switch calculate the soc, soh and cycle
    switch(batSox->batStates)
    {
        case BAT_INITIALIZED_WITHOUT_CALIBRATION ... BAT_INITIALIZED:
        {
            batSox->sumOfCapacityChange += ABSOLUTE(batSox->previousCapacity - batSox->batInstantaneousCapacity);
            batSox->previousCapacity = batSox->batInstantaneousCapacity;

            if(passingCurrent == 0)
            {
                if(batSox->sumOfCapacityChange > SOH_CALCULATE_PERIOD)       //if total voltage change is > 1V recalculate soh
                {
                    batSox->sumOfCapacityChange = 0.0f;
                    batSox->batStates = BAT_IDLE_MODE;
                }
            }
            else if(passingCurrent > 0)
            {
                batSox->batStates = BAT_CHARGING_MODE;
            }
            else if(passingCurrent < 0)
            {
                batSox->batStates = BAT_DISCHARGING_MODE;
            }
            else
            {
                batSox->batStates = BAT_NO_OPERATION;
            }

            switch(batSox->batStates)
            {
                case BAT_NO_OPERATION:
                {
                    break;
                }
                case BAT_IDLE_MODE:             //calculate SOH
                {
                    CellTable_ts moliTab = AE_tableFindByVoltage(meanCellVolt, CELL_TABLE_IDLE);

                    uint16_t dodRatio = 100 - soxInitVals.cellLowerDocRatio - soxInitVals.cellUpperDocRatio;
                    float systemInitialCap = moliTab.capacity * dodRatio / 100.0f;

                    batSox->soh = (batSox->batInstantaneousCapacity / systemInitialCap) * 100.0f;

                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;
                    break;
                }
                case BAT_CHARGING_MODE:         //calculate SOC and Cycle number
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->soc += passingCurrent / soxInitVals.batDodCapacity * 100.0f;
                    batSox->cycle += (passingCurrent / soxInitVals.batDodCapacity) / 2;

                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;
                    break;
                }
                case BAT_DISCHARGING_MODE:      //calculate SOC and Cycle number
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->soc += passingCurrent / soxInitVals.batDodCapacity * 100.0f;
                    batSox->cycle -= (passingCurrent / soxInitVals.batDodCapacity) / 2;

                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;
                    break;
                }
            }
        }
    }
}

static BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void)
{
    //Bu fonksiyon i�erisinde eepromdan okunan BatSoxVal_ts de�erleri atanacak
    //test etmek i�in bo� b�rak�ld� SOH = 100, SOC = 0, Cycle = 0 olarak kabul edildi
    BatSoxVal_ts batSoxEeprom =
    {
         .batInstantaneousCapacity = 0.0f,
         .batStates = BAT_NOT_INITIALIZED,
         .cycle = 0.0f,
         .soc = 0.0f,
         .soh = 100.0f,
         .sumOfCapacityChange = 0,
    };

    return batSoxEeprom;
}

