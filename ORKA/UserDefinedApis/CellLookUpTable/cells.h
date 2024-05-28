/*
 * molicel.h
 *
 *  Created on: 21 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLS_H_
#define ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLS_H_

#include <stdint.h>

//!< @refgroup MOLICEL_TABLE_
#define CELL_TABLE_IDLE              (0x01)
#define CELL_TABLE_CHARGING          (0x02)  //010
#define CELL_TABLE_DISCHARGING       (0x04)  //100
#define CELL_TABLE_SIZE              (101u)

#define CELL_MOLICEL_PB45            (0x00)
#define CELL_ASPILSAN_xx             (0x01)

#define USING_CELL                   (CELL_MOLICEL_PB45)

#define MIN_CELL_VOLTAGE             (molicelChargeTable[CELL_TABLE_SIZE - 1].voltage)
#define MAX_CELL_VOLTAGE             (moliceDischargeTable[0].voltage)
#define MAX_CELL_CAPACITY            (molicelChargeTable[0].capacity)

typedef struct CellTable_s{
    double capacity;
    double voltage;
    double resistance;
}CellTable_ts;

#if USING_CELL == CELL_MOLICEL_PB45

extern const CellTable_ts moliceDischargeTable[CELL_TABLE_SIZE];
extern const CellTable_ts molicelChargeTable[CELL_TABLE_SIZE];
extern const CellTable_ts molicelIdleChargeTable[CELL_TABLE_SIZE];

#endif

#endif /* ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLS_H_ */
