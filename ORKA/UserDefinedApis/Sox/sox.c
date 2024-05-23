/*
 * sox.c
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#include "sox.h"
#include "MolicelLookUpTable/molicel.h"

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

    soxInitVals.batTotatlCapacity = cellCapacityInmAh * numberOfParallelCell;
    soxInitVals.batDodCapacity    = cellCapacityInmAh * numberOfParallelCell * dod / 100.0f;

    //calculate the minimum and maximum voltage according to dod
    float batCapacity = (soxInit->cellCapacityInmAh * batSox.soh / 100.0f);
    uint32_t dodLowerCapacity = (batCapacity * soxInitVals.cellLowerDocRatio) / 100.0f;
    uint32_t dodUpperCapacity = (batCapacity * (100 - soxInitVals.cellUpperDocRatio)) / 100.0f;

    MolicelTable_ts moliTab = {0};
    moliTab = AE_molicelFindByCapacity(dodLowerCapacity, MOLICEL_TABLE_IDLE);
    soxInitVals.minDischargeVoltage = moliTab.voltage;

    moliTab = AE_molicelFindByCapacity(dodUpperCapacity, MOLICEL_TABLE_IDLE);
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
    switch(batSox->batStates)
    {
        case BAT_NOT_INITIALIZED:       //work only one after this time read from the eeprom
        {
            if(meanCellVolt >= soxInitVals.maxChargeVoltage)
            {
                batSox->batStates = BAT_UPPER_DOD_POINT;
            }
            else if(meanCellVolt <= soxInitVals.minDischargeVoltage)
            {
                batSox->batStates = BAT_LOWER_DOD_POINT;
            }
            break;
        }
        case BAT_UPPER_DOD_POINT:       //enter only one times
        {
            batSox->soc = 100.0f;
            batSox->batInstantaneousCapacity = soxInitVals.batDodCapacity;
            batSox->batStates = BAT_INITIALIZED;
            break;
        }
        case BAT_LOWER_DOD_POINT:       //enter only one times
        {
            batSox->soc = 0.0f;
            batSox->batStates = BAT_INITIALIZED;
            break;
        }
        case BAT_INITIALIZED:
        {
            if(passingCurrent == 0)
            {
                batSox->batStates = BAT_IDLE_MODE;
            }
            else if(passingCurrent > 0)
            {
                batSox->batStates = BAT_CHARGING_MODE;
            }
            else
            {
                batSox->batStates = BAT_DISCHARGING_MODE;
            }

            switch(batSox->batStates)
            {
                case BAT_IDLE_MODE:
                {
                    MolicelTable_ts moliTab = AE_molicelFindByVoltage(meanCellVolt, MOLICEL_TABLE_IDLE);

                    uint16_t dodRatio = 100 - soxInitVals.cellLowerDocRatio - soxInitVals.cellUpperDocRatio;
                    float systemInitialCap = moliTab.capacity * dodRatio / 100.0f;

                    batSox->soh = batSox->batInstantaneousCapacity / systemInitialCap;

                    batSox->batStates = BAT_INITIALIZED;
                    break;
                }
                case BAT_CHARGING_MODE:
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->soc += passingCurrent / soxInitVals.batDodCapacity * 100.0f;
                    batSox->cycle += (passingCurrent / soxInitVals.batDodCapacity) / 2;

                    batSox->batStates = BAT_INITIALIZED;
                    break;
                }
                case BAT_DISCHARGING_MODE:
                {
                    batSox->batInstantaneousCapacity += passingCurrent;
                    batSox->soc += passingCurrent / soxInitVals.batDodCapacity * 100.0f;
                    batSox->cycle -= (passingCurrent / soxInitVals.batDodCapacity) / 2;

                    batSox->batStates = BAT_INITIALIZED;
                    break;
                }
            }
        }
    }
}

static BatSoxVal_ts AE_readBatSoxDatasFromEeprom(void)
{
    //Bu fonksiyon içerisinde eepromdan okunan BatSoxVal_ts deðerleri atanacak
    //test etmek için boþ býrakýldý SOH = 100, SOC = 0, Cycle = 0 olarak kabul edildi
    BatSoxVal_ts batSoxEeprom =
    {
         .batInstantaneousCapacity = 0.0f,
         .batStates = BAT_NOT_INITIALIZED,
         .cycle = 0.0f,
         .soc = 0.0f,
         .soh = 100.0f
    };

    return batSoxEeprom;
}

