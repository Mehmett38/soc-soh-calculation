/*
 * cellLookupTable.c
 *
 *  Created on: 23 May 2024
 *      Author: mehmet.dincer
 */


#include <CellLookUpTable/cellLookupTable.h>

static CellTable_ts AE_findIndexByVoltage(CellTable_ts const * tableName, float voltage);
static CellTable_ts AE_findIndexByCapacity(CellTable_ts const * tableName, uint32_t capacity);
static CellTable_ts AE_interpolationByCapacity(CellTable_ts index1, CellTable_ts index2, uint32_t capacity);
static CellTable_ts AE_interpolationByVoltage(CellTable_ts index1, CellTable_ts index2, float voltage);

/**
 * @find the capacity and resistance by using the voltage
 * @param[in] voltage value for param search @refgroup MOLICEL_TABLE_
 * @return MolicelTable_ts
 */
CellTable_ts AE_tableFindByVoltage(float voltage, uint8_t MOLICEL_TABLE_)
{
    if(MOLICEL_TABLE_ & 0x01)       // if charging or idle mode
    {
        return AE_findIndexByVoltage(molicelIdleChargeTable, voltage);
    }
    else if(MOLICEL_TABLE_ & 0x02)
    {
        return AE_findIndexByVoltage(molicelChargeTable, voltage);
    }
    else
    {
        return AE_findIndexByVoltage(moliceDischargeTable, voltage);
    }
}


/**
 * @find the capacity and resistance by using the c
 * @param[in] voltage value for param search @refgroup MOLICEL_TABLE_
 * @return MolicelTable_ts
 */
CellTable_ts AE_tableFindByCapacity(uint32_t capacity, uint8_t MOLICEL_TABLE_)
{
    if(MOLICEL_TABLE_ & 0x01)       // if charging or idle mode
    {
        return AE_findIndexByCapacity(molicelIdleChargeTable, capacity);
    }
    else if(MOLICEL_TABLE_ & 0x02)
    {
        return AE_findIndexByCapacity(molicelChargeTable, capacity);
    }
    else
    {
        return AE_findIndexByCapacity(moliceDischargeTable, capacity);
    }
}

/**
 * @brief interpolate the table by linearize the two index that is consecutive
 * @param[in] cell Lookup table addres
 * @param[in] index that is sub point of linearized point
 * @return[in] interpolated cell index values
 */
static CellTable_ts AE_interpolationByCapacity(CellTable_ts index1, CellTable_ts index2, uint32_t capacity)
{
    CellTable_ts cellTemp = index1;

    float slope = 0.0f;
    float offset = 0.0f;

    slope = (index2.voltage - index1.voltage) / (index2.capacity - index1.capacity);
    offset = index1.voltage - (index1.capacity * slope);

    float voltage = capacity * slope + offset;         // ax + b

    if(voltage < MIN_CELL_VOLTAGE)
    {
        cellTemp.voltage = MIN_CELL_VOLTAGE;
    }
    else if(voltage < MAX_CELL_VOLTAGE)
    {
        cellTemp.voltage = voltage;
    }
    else
    {
        cellTemp.voltage = MAX_CELL_VOLTAGE;
    }

    return cellTemp;
}

static CellTable_ts AE_interpolationByVoltage(CellTable_ts index1, CellTable_ts index2, float voltage)
{
    CellTable_ts cellTemp = index1;

    float slope = 0.0f;
    float offset = 0.0f;

    slope = (index2.capacity - index1.capacity) / (index2.voltage - index1.voltage);
    offset = index1.capacity - (index1.voltage * slope);

    float capacity = voltage * slope + offset;         // ax + b

    if(voltage < 0)
    {
        cellTemp.capacity = 0;
    }
    else if(voltage < MAX_CELL_CAPACITY)
    {
        cellTemp.capacity = capacity;
    }
    else
    {
        cellTemp.capacity = MAX_CELL_CAPACITY;
    }


    return cellTemp;
}


/**
 * @brief find the related MolicelTable_ts by using table name
 * @param[in] molicelChargeTable or moliceDischargeTable
 */
static CellTable_ts AE_findIndexByVoltage(CellTable_ts const * tableName, float voltage)
{
    CellTable_ts returnIndex;

    if(voltage >= tableName[0].voltage)
    {
        returnIndex = tableName[0];
    }
    else if(voltage <= tableName[CELL_TABLE_SIZE - 1].voltage)
    {
        returnIndex = tableName[CELL_TABLE_SIZE - 1];
    }
    else
    {
        for(int i = 0; i < (CELL_TABLE_SIZE - 1); i++)
        {
            if(voltage >= tableName[i].voltage)
            {
                returnIndex = AE_interpolationByVoltage(tableName[i], tableName[i-1], voltage);
                break;
            }
        }
    }

    return returnIndex;
}

/**
 * @brief find the related MolicelTable_ts by using table name
 * @param[in] molicelChargeTable or moliceDischargeTable
 */
static CellTable_ts AE_findIndexByCapacity(CellTable_ts const * tableName, uint32_t capacity)
{
    CellTable_ts returnIndex;

    if(capacity >= tableName[0].capacity)
    {
        returnIndex = tableName[0];
    }
    else if(capacity <= tableName[CELL_TABLE_SIZE - 1].capacity)
    {
        returnIndex = tableName[CELL_TABLE_SIZE - 1];
    }
    else
    {
        for(int i = 0; i < CELL_TABLE_SIZE; i++)
        {
            if(capacity >= tableName[i].capacity)
            {
                returnIndex = AE_interpolationByCapacity(tableName[i], tableName[i - 1], capacity);
                break;
            }
        }
    }

    return returnIndex;
}



