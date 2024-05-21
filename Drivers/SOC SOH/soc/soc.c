/*
 * soc.c
 *
 *  Created on: 26 Þub 2024
 *      Author: mehmet.dincer
 */


#include "soc.h"

SocState socState;

static void AE_charge();
static void AE_discharge();

/**
 * @brief read the eeprom to take last variables
 */
void AE_socInitialize()
{
    /*
     * !!!NOTE
     * bu alan içerisinde eeprom'un belirli adresine batarya initialize flag eklensin
     * bu flag'in deðeri daha önceden kaydedilmiþse 1982 olsun
     * bu adresi okuduðumuzda 1982 okursak soh,soc deðerlerini ilk baþta eepromdan alsýn
     * diðer durumda look up table'a bakmasý gerekir
     * ilk durum daha sonra yazýlacaktýr
     */
    if(0)
    {
        // Bu kýsým daha sonra yazýlacak
    }
    else
    {
        socState.soh = 100;
        socState.batteryCapacity = 4500;

        socState.socRatio = 0;
    }
}

/**
 * @brief calculate the soc
 */
void AE_calculateSoc()
{
    if(crcBuffer.rxCurrent > 0)
    {
        AE_charge();
    }
    else
    {
        AE_discharge();
    }
}

static void AE_charge()
{
    socState.totalCurrent += crcBuffer.rxCurrent;
    socState.cycle += (crcBuffer.rxCurrent / 4500.0f) / 2.0f;
    socState.socRatio = (socState.totalCurrent / socState.batteryCapacity) * 100.0f;
}

static void AE_discharge()
{
    socState.totalCurrent += crcBuffer.rxCurrent;
    if(socState.totalCurrent < 0)
        socState.totalCurrent = 0;

    socState.cycle -= (crcBuffer.rxCurrent / 4500.0f) / 2.0f;
    socState.socRatio = (socState.totalCurrent / socState.batteryCapacity) * 100.0f;
}














