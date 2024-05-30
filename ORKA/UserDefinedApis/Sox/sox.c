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
static void AE_calculateMinMaxVoltage(void);

/**
 * @brief
 * @param[in]
 * @return none
 */
void AE_soxInit(SoxInitTypeDef_ts * soxInit)
{
    //copy battery information
    soxInitVals = *soxInit;

    //calculate the system capacity
    soxInitVals.dodRatio = (100 - soxInitVals.cellLowerDocRatio - soxInitVals.cellUpperDocRatio) / 100.0f;

    soxInitVals.cellCapacityInmAh *= soxInitVals.numberOfParallelCell;
    soxInitVals.batDodCapacity = soxInitVals.cellCapacityInmAh * soxInitVals.dodRatio;
    soxInitVals.batNetCapacity = batSox.batTotalCapacity; //used for the initialized systems

    //calculate the minimum and maximum voltage according to dod
    soxInitVals.batMinDodCapacity = (soxInitVals.cellCapacityInmAh * soxInitVals.cellLowerDocRatio) / 100.0f;
    soxInitVals.batMaxDodCapacity = (soxInitVals.cellCapacityInmAh * (100 - soxInitVals.cellUpperDocRatio)) / 100.0f;
    soxInitVals.batTempMaxDodCapacity = soxInitVals.batMaxDodCapacity;

    //calibrate the upper DOC ratio according to system SOH value
    AE_dodCalibrate(&batSox);
}

/**
 * @brief calculate the soc and soh
 * @param[in] batSox states global variable
 * @param[in] instantaneous passing current
 * @param[in] meaning cell voltage of the cell in the battery
 * @none
 */
void AE_soxCalculate_UML(BatSoxVal_ts * batSox, float passingCurrent, float systemTotalVolt)
{
    float meanCellVolt = systemTotalVolt / soxInitVals.numberOfSerialCell;

    //!< first switch check the system is initialized and calibrated
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
            batSox->batCalibrationState = (batSox->batCalibrationState == BAT_WAIT_FOR_UPPER_DOD_POINT) ? BAT_CALIBRATED : BAT_WAIT_FOR_LOWER_DOD_POINT;
            batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED)? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

            if(batSox->batStates == BAT_INITIALIZED)
            {   //TODO bu degerleri fonksyion icerisine yaz
                soxInitVals.batNetCapacity = batSox->batInstantaneousCapacity;
                batSox->batTotalCapacity = soxInitVals.batNetCapacity;
                //calibration soh is system dead calibration rati + DOC ratio ; DOC = 1 - DOD
                batSox->calibrationSoh = (batSox->batTotalCapacity / soxInitVals.dodRatio) / SYSTEM_TOTAL_CAPACITY;
                batSox->soc = 100.0f;
                batSox->cycle = 0.0f;
                batSox->soh = 100.0f;
                batSox->sumOfCapacityChange = 0.0f;
                AE_dodCalibrate(batSox);
            }

            break;
        }
        case BAT_LOWER_DOD_POINT:       //enter only one times
        {
            batSox->batCalibrationState = (batSox->batCalibrationState == BAT_WAIT_FOR_LOWER_DOD_POINT) ? BAT_CALIBRATED : BAT_WAIT_FOR_UPPER_DOD_POINT;
            batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED)? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

            if(batSox->batStates == BAT_INITIALIZED)
            {   //TODO bu degerleri fonksyion icerisine yaz
                soxInitVals.batNetCapacity = -batSox->batInstantaneousCapacity;
                batSox->batTotalCapacity = soxInitVals.batNetCapacity;
                batSox->batInstantaneousCapacity = 0;
                //calibration soh is system dead calibration rati + DOC ratio ; DOC = 1 - DOD
                batSox->calibrationSoh = (batSox->batTotalCapacity / soxInitVals.dodRatio) / SYSTEM_TOTAL_CAPACITY;
                batSox->soc = 0.0f;
                batSox->cycle = 0.0f;
                batSox->soh = 100.0f;
                batSox->sumOfCapacityChange = 0.0f;
                AE_dodCalibrate(batSox);
            }

            break;
        }
    }

    //!< second switch calculate the soc, soh and cycle
    switch(batSox->batStates)
    {
        case BAT_INITIALIZED_WITHOUT_CALIBRATION ... BAT_INITIALIZED:
        {
            batSox->sumOfCapacityChange += fabs(batSox->previousCapacity - batSox->batInstantaneousCapacity);
            batSox->previousCapacity = batSox->batInstantaneousCapacity;

            if(passingCurrent == 0)
            {
                if(batSox->batStates == BAT_INITIALIZED_WITHOUT_CALIBRATION)    //clear the sum of capacity change period
                {
                    batSox->sumOfCapacityChange = 0;
                    break;
                }

                if(batSox->sumOfCapacityChange > SOH_CALCULATE_PERIOD)       //if total voltage change is > 1V recalculate soh
                {
                    /*Since the capacity value changes a lot below this voltage value,
                    there is a deviation in the SOH value,
                    therefore SOH is calculated at voltage values above 3.3V.*/
                    if(meanCellVolt < 3.3f)
                    {
                        batSox->sumOfCapacityChange = SOH_CALCULATE_PERIOD / 2.0f;
                    }
                    else
                    {
                        batSox->sumOfCapacityChange = 0.0f;
                        batSox->batStates = BAT_IDLE_MODE;
                    }
                }
            }
            else if(passingCurrent > 0)
            {
                batSox->batStates = BAT_CHARGING_MODE;
            }
            else //passingCurrent < 0
            {
                batSox->batStates = BAT_DISCHARGING_MODE;
            }

            switch(batSox->batStates)
            {
                case BAT_NO_OPERATION:
                {
                    break;
                }
                case BAT_IDLE_MODE:             //calculate SOH
                {
                    //take the system capacity according to mean voltage
                    CellTable_ts moliTab = AE_tableFindByVoltage(meanCellVolt, soxInitVals.numberOfParallelCell, CELL_TABLE_IDLE);
                    float systemInitialCap = (moliTab.capacity * batSox->calibrationSoh) - soxInitVals.batMinDodCapacity;

                    //calculate the SOH by using calculated capacity and system capacity according to voltage
                    batSox->soh = (batSox->batInstantaneousCapacity / systemInitialCap) * 100.0f;

                    //calculate the system capacity according to SOH
                    batSox->batTotalCapacity = soxInitVals.batNetCapacity * (batSox->soh / 100.0f);

                    //calibrate the upper doc value according to system SOH change
                    AE_dodCalibrate(batSox);

                    //limit the SOH
                    batSox->soh = (batSox->soh > 100.0) ? 100 : batSox->soh; //limit the SOH

                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;
                    break;
                }
                case BAT_CHARGING_MODE:         //calculate SOC and Cycle number
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

                    if(batSox->batCalibrationState != BAT_CALIBRATED)
                        break;
                    batSox->soc += passingCurrent / batSox->batTotalCapacity * 100.0f;
                    batSox->soc = (batSox->soc > 100.0) ? 100 : batSox->soc;
                    batSox->cycle += (passingCurrent / batSox->batTotalCapacity) / 2.0f;

                    break;
                }
                case BAT_DISCHARGING_MODE:      //calculate SOC and Cycle number
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->batStates = (batSox->batCalibrationState == BAT_CALIBRATED) ? BAT_INITIALIZED : BAT_INITIALIZED_WITHOUT_CALIBRATION;

                    if(batSox->batCalibrationState != BAT_CALIBRATED)
                        break;
                    batSox->soc += passingCurrent / batSox->batTotalCapacity* 100.0f;
                    batSox->soc = (batSox->soc < 0.0) ? 0 : batSox->soc;
                    batSox->cycle -= (passingCurrent / batSox->batTotalCapacity) / 2.0f;

                    break;
                }
            }
        }
    }
}

/**
 * @brief recalculate the *upper dod ratio according the first system capacity value
 * @note call this function inside of idle current SOH update case and with the calibratioSoh variable
 */
void AE_dodCalibrate(BatSoxVal_ts * batSox)
{
    if(batSox->batStates == BAT_NOT_INITIALIZED)
    {
        AE_calculateMinMaxVoltage();
        return;
    }

    //Total capacity value will decrease over time,
    float totolCapacityOffset = soxInitVals.batDodCapacity - batSox->batTotalCapacity;
    float upperDocValue = (soxInitVals.cellCapacityInmAh - soxInitVals.batMaxDodCapacity) - totolCapacityOffset;

    //new dodMaxCapacity
    soxInitVals.batTempMaxDodCapacity = soxInitVals.cellCapacityInmAh - upperDocValue;

    //update upper upper dod value and dod ratio
    soxInitVals.cellUpperDocRatio =  (upperDocValue / soxInitVals.cellCapacityInmAh) * 100.0f;
    soxInitVals.dodRatio = (100 - soxInitVals.cellLowerDocRatio - soxInitVals.cellUpperDocRatio) / 100.0f;

    AE_calculateMinMaxVoltage();
}

/**
 * @brief calculate the min and max voltage according to dod change
 * @return none
 */
static void AE_calculateMinMaxVoltage(void)
{
    //calculate the min and max voltage according to DOD
    CellTable_ts moliTab = {0};
    moliTab = AE_tableFindByCapacity(soxInitVals.batMinDodCapacity, soxInitVals.numberOfParallelCell, CELL_TABLE_DISCHARGING);
    soxInitVals.minDischargeVoltage = moliTab.voltage;

    moliTab = AE_tableFindByCapacity(soxInitVals.batTempMaxDodCapacity, soxInitVals.numberOfParallelCell, CELL_TABLE_CHARGING);
    soxInitVals.maxChargeVoltage = moliTab.voltage;
}

/**
 * @brief read sox datas from eeprom
 * @return previous batSox datas
 */
BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void)
{
    //bu fonksiyon icierisindeki degerler sistem initialize edildikten sonra eepromdan okunmasi planlanmistir
    //bu nedenle BAT_NOT_INITIALIZED makrosu hayati onem tasimaktadir
    BatSoxVal_ts batSoxEeprom =
    {
         .batInstantaneousCapacity = 0.0f,
         .batStates = BAT_NOT_INITIALIZED,
         .batTotalCapacity = 4500,
         .cycle = 0.0f,
         .soc = 0.0f,
         .soh = 100.0f,
         .sumOfCapacityChange = 0,
    };

    return batSoxEeprom;
}

