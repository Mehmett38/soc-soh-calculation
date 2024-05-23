/*
 * molicel.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_USERDEFINEDAPIS_MOLICELLOOKUPTABLE_MOLICEL_H_
#define ORKA_USERDEFINEDAPIS_MOLICELLOOKUPTABLE_MOLICEL_H_

#include <stdint.h>

//!< @refgroup MOLICEL_TABLE_
#define MOLICEL_TABLE_IDLE              (0x00)
#define MOLICEL_TABLE_DISCHARGING       (0x00)  //100
#define MOLICEL_TABLE_CHARGING          (0x01)  //010

#define MOLICEL_TABLE_SIZE              (101u)

typedef struct MolicelTable_s{
    uint32_t capacity;
    float voltage;
    float resistance;
}MolicelTable_ts;


extern const MolicelTable_ts molicelChargeTable[MOLICEL_TABLE_SIZE] =
{
     {4500, 4.1803f, 13.437f},
     {4455, 4.1781f, 13.439f},
     {4410, 4.1737f, 13.451f},
     {4365, 4.1675f, 13.459f},
     {4320, 4.1598f, 13.479f},
     {4275, 4.1509f, 13.500f},
     {4230, 4.1411f, 13.520f},
     {4185, 4.1305f, 13.562f},
     {4140, 4.1194f, 13.570f},
     {4095, 4.108f, 13.5990f},
     {4050, 4.0964f, 13.629f},
     {4005, 4.0847f, 13.650f},
     {3960, 4.0731f, 13.695f},
     {3915, 4.0616f, 13.763f},
     {3870, 4.0504f, 13.765f},
     {3825, 4.0394f, 13.802f},
     {3780, 4.0287f, 13.838f},
     {3735, 4.0185f, 13.858f},
     {3690, 4.0085f, 13.860f},
     {3645, 3.999f, 13.8630f},
     {3600, 3.9898f, 13.870f},
     {3555, 3.981f, 13.876f},
     {3510, 3.9726f, 13.886f},
     {3465, 3.9644f, 13.895f},
     {3420, 3.9566f, 13.905f},
     {3375, 3.949f, 13.91f},
     {3330, 3.9416f, 13.913f},
     {3285, 3.9344f, 13.921f},
     {3240, 3.9274f, 13.939f},
     {3195, 3.9204f, 13.952f},
     {3150, 3.9135f, 13.953f},
     {3105, 3.9066f, 13.973f},
     {3060, 3.8996f, 13.988f},
     {3015, 3.8926f, 13.988f},
     {2970, 3.8854f, 14.012f},
     {2925, 3.8781f, 14.027f},
     {2880, 3.8707f, 14.055f},
     {2835, 3.863f, 14.061f},
     {2790, 3.8551f, 14.062f},
     {2745, 3.8469f, 14.066f},
     {2700, 3.8384f, 14.077f},
     {2655, 3.8297f, 14.101f},
     {2610, 3.8207f, 14.105f},
     {2565, 3.8114f, 14.131f},
     {2520, 3.8017f, 14.133f},
     {2475, 3.7918f, 14.14f},
     {2430, 3.7817f, 14.148f},
     {2385, 3.7713f, 14.168f},
     {2340, 3.7606f, 14.172f},
     {2295, 3.7497f, 14.185f},
     {2250, 3.7387f, 14.188f},
     {2205, 3.7275f, 14.196f},
     {2160, 3.7162f, 14.2f},
     {2115, 3.7049f, 14.244f},
     {2070, 3.6935f, 14.263f},
     {2025, 3.6821f, 14.28f},
     {1980, 3.6709f, 14.291f},
     {1935, 3.6597f, 14.321f},
     {1890, 3.6487f, 14.336f},
     {1845, 3.6379f, 14.373f},
     {1800, 3.6274f, 14.379f},
     {1755, 3.6171f, 14.417f},
     {1710, 3.6073f, 14.417f},
     {1665, 3.5978f, 14.451f},
     {1620, 3.5887f, 14.455f},
     {1575, 3.5801f, 14.479f},
     {1530, 3.572f, 14.485f},
     {1485, 3.5643f, 14.501f},
     {1440, 3.5572f, 14.507f},
     {1395, 3.5505f, 14.517f},
     {1350, 3.5443f, 14.518f},
     {1305, 3.5386f, 14.521f},
     {1260, 3.5333f, 14.526f},
     {1215, 3.5284f, 14.527f},
     {1170, 3.5238f, 14.79f},
     {1125, 3.5194f, 15.099f},
     {1080, 3.5151f, 15.446f},
     {1035, 3.5107f, 15.831f},
     {990, 3.5062f, 16.256f},
     {945, 3.5013f, 16.72f},
     {900, 3.4959f, 17.225f},
     {855, 3.4897f, 17.77f},
     {810, 3.4825f, 18.355f},
     {765, 3.4739f, 18.979f},
     {720, 3.4637f, 19.64f},
     {675, 3.4515f, 20.339f},
     {630, 3.4369f, 21.071f},
     {585, 3.4195f, 21.835f},
     {540, 3.3989f, 22.629f},
     {495, 3.3744f, 23.448f},
     {450, 3.3455f, 24.288f},
     {405, 3.3117f, 25.145f},
     {360, 3.2722f, 26.013f},
     {315, 3.2264f, 26.886f},
     {270, 3.1735f, 27.758f},
     {225, 3.1127f, 28.621f},
     {180, 3.0431f, 29.467f},
     {135, 2.9637f, 30.287f},
     {90, 2.8736f, 31.069f},
     {45, 2.7716f, 31.805f},
     {1, 2.6567f, 32.481f}
};

extern const MolicelTable_ts moliceDischargeTable[MOLICEL_TABLE_SIZE] =
{
     {4500, 4.1609f, 13.225f},
     {4455, 4.1556f, 13.231f},
     {4410, 4.1493f, 13.237f},
     {4365, 4.1420f, 13.257f},
     {4320, 4.1339f, 13.265f},
     {4275, 4.1252f, 13.304f},
     {4230, 4.1160f, 13.306f},
     {4185, 4.1064f, 13.360f},
     {4140, 4.0965f, 13.375f},
     {4095, 4.0864f, 13.424f},
     {4050, 4.0761f, 13.471f},
     {4005, 4.0658f, 13.496f},
     {3960, 4.0554f, 13.575f},
     {3915, 4.0451f, 13.595f},
     {3870, 4.0348f, 13.597f},
     {3825, 4.0247f, 13.599f},
     {3780, 4.0146f, 13.608f},
     {3735, 4.0047f, 13.615f},
     {3690, 3.9950f, 13.635f},
     {3645, 3.9853f, 13.641f},
     {3600, 3.9759f, 13.660f},
     {3555, 3.9666f, 13.678f},
     {3510, 3.9574f, 13.679f},
     {3465, 3.9484f, 13.725f},
     {3420, 3.9395f, 13.739f},
     {3375, 3.9307f, 13.747f},
     {3330, 3.9220f, 13.747f},
     {3285, 3.9134f, 13.778f},
     {3240, 3.9049f, 13.818f},
     {3195, 3.8964f, 13.837f},
     {3150, 3.8879f, 13.838f},
     {3105, 3.8794f, 13.903f},
     {3060, 3.8709f, 13.916f},
     {3015, 3.8624f, 13.927f},
     {2970, 3.8538f, 13.931f},
     {2925, 3.8452f, 13.971f},
     {2880, 3.8365f, 14.017f},
     {2835, 3.8277f, 14.034f},
     {2790, 3.8187f, 14.041f},
     {2745, 3.8097f, 14.104f},
     {2700, 3.8005f, 14.113f},
     {2655, 3.7912f, 14.148f},
     {2610, 3.7817f, 14.173f},
     {2565, 3.7721f, 14.184f},
     {2520, 3.7623f, 14.188f},
     {2475, 3.7524f, 14.254f},
     {2430, 3.7424f, 14.268f},
     {2385, 3.7321f, 14.321f},
     {2340, 3.7218f, 14.332f},
     {2295, 3.7113f, 14.343f},
     {2250, 3.7007f, 14.385f},
     {2205, 3.6899f, 14.398f},
     {2160, 3.6791f, 14.411f},
     {2115, 3.6681f, 14.444f},
     {2070, 3.6571f, 14.473f},
     {2025, 3.6460f, 14.498f},
     {1980, 3.6348f, 14.513f},
     {1935, 3.6235f, 14.527f},
     {1890, 3.6123f, 14.546f},
     {1845, 3.6009f, 14.573f},
     {1800, 3.5896f, 14.587f},
     {1755, 3.5783f, 14.610f},
     {1710, 3.5669f, 14.620f},
     {1665, 3.5555f, 14.639f},
     {1620, 3.5442f, 14.645f},
     {1575, 3.5328f, 14.658f},
     {1530, 3.5214f, 14.662f},
     {1485, 3.5100f, 14.669f},
     {1440, 3.4986f, 14.670f},
     {1395, 3.4871f, 14.685f},
     {1350, 3.4756f, 14.715f},
     {1305, 3.4639f, 14.938f},
     {1260, 3.4520f, 15.010f},
     {1215, 3.4400f, 15.182f},
     {1170, 3.4277f, 15.373f},
     {1125, 3.4151f, 15.446f},
     {1080, 3.4021f, 15.730f},
     {1035, 3.3886f, 15.776f},
     {990, 3.3746f, 16.220f},
     {945, 3.3598f, 16.706f},
     {900, 3.3443f, 17.236f},
     {855, 3.3278f, 17.808f},
     {810, 3.3102f, 18.424f},
     {765, 3.2913f, 19.084f},
     {720, 3.2711f, 19.787f},
     {675, 3.2491f, 20.534f},
     {630, 3.2254f, 21.324f},
     {585, 3.1995f, 22.155f},
     {540, 3.1713f, 23.026f},
     {495, 3.1405f, 23.936f},
     {450, 3.1067f, 24.883f},
     {405, 3.0697f, 25.864f},
     {360, 3.0291f, 26.877f},
     {315, 2.9846f, 27.918f},
     {270, 2.9357f, 28.984f},
     {225, 2.882f, 30.0710f},
     {180, 2.823f, 31.1730f},
     {135, 2.7583f, 32.287f},
     {90, 2.6874f, 33.406f},
     {45, 2.6097f, 34.524f},
     {1, 2.5246f, 35.6340f}
};

/**
 * @brief find the related MolicelTable_ts by using table name
 * @param[in] molicelChargeTable or moliceDischargeTable
 */
#define FIND_MOLICELL_TABLE_BY_VOLTAGE(tableName)                       \
        if(voltage >= tableName[0].voltage)                             \
        {                                                               \
            return tableName[0];                                        \
        }                                                               \
        else if(voltage <= tableName[MOLICEL_TABLE_SIZE - 1].voltage)   \
        {                                                               \
            return tableName[MOLICEL_TABLE_SIZE - 1];                   \
        }                                                               \
        else                                                            \
        {                                                               \
            for(int i = 1; i < (MOLICEL_TABLE_SIZE - 1); i++)           \
            {                                                           \
                if(voltage >= tableName[i].voltage)                     \
                {                                                       \
                    return tableName[i];                                \
                }                                                       \
            }                                                           \
        }

/**
 * @find the capacity and resistance by using the voltage
 * @param[in] voltage value for param search @refgroup MOLICEL_TABLE_
 * @return MolicelTable_ts
 */
static MolicelTable_ts AE_molicelFindByVoltage(float voltage, uint8_t MOLICEL_TABLE_)
{
    MolicelTable_ts moliTab = {0};

    if(MOLICEL_TABLE_)       // if charging or idle mode
    {
        FIND_MOLICELL_TABLE_BY_VOLTAGE(molicelChargeTable);
    }

    FIND_MOLICELL_TABLE_BY_VOLTAGE(moliceDischargeTable);

    return moliTab;
}

/**
 * @brief find the related MolicelTable_ts by using table name
 * @param[in] molicelChargeTable or moliceDischargeTable
 */
#define FIND_MOLICELL_TABLE_BY_CAPACITY(tableName)                     \
        if(capacity >= tableName[0].capacity)                          \
        {                                                              \
            return tableName[0];                                       \
        }                                                              \
        else if(capacity <= tableName[MOLICEL_TABLE_SIZE - 1].capacity)\
        {                                                              \
            return tableName[MOLICEL_TABLE_SIZE - 1];                  \
        }                                                              \
        else                                                           \
        {                                                              \
            for(int i = 1; i < (MOLICEL_TABLE_SIZE - 1); i++)          \
            {                                                          \
                if(capacity >= tableName[i].capacity)                  \
                {                                                      \
                    return tableName[i];                               \
                }                                                      \
            }                                                          \
        }

/**
 * @find the capacity and resistance by using the c
 * @param[in] voltage value for param search @refgroup MOLICEL_TABLE_
 * @return MolicelTable_ts
 */
static MolicelTable_ts AE_molicelFindByCapacity(uint32_t capacity, uint8_t MOLICEL_TABLE_)
{
    MolicelTable_ts moliTab = {0};

    if(MOLICEL_TABLE_)       // if charging or idle mode
    {
        FIND_MOLICELL_TABLE_BY_CAPACITY(molicelChargeTable);
    }

    FIND_MOLICELL_TABLE_BY_CAPACITY(moliceDischargeTable);

    return moliTab;
}


#endif /* ORKA_USERDEFINEDAPIS_MOLICELLOOKUPTABLE_MOLICEL_H_ */
