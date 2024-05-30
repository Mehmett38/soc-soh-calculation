/*
 * cellLookupTable.h
 *
 *  Created on: 23 May 2024
 *      Author: mehmet.dincer
 */

#ifndef ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLLOOKUPTABLE_H_
#define ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLLOOKUPTABLE_H_

#include <cells.h>
#include <stdint.h>

CellTable_ts AE_tableFindByCapacity(uint32_t capacity, uint16_t numberOfParallelCell, uint8_t MOLICEL_TABLE_);
CellTable_ts AE_tableFindByVoltage(double voltage, uint16_t numberOfParallelCell, uint8_t MOLICEL_TABLE_);

#endif /* ORKA_USERDEFINEDAPIS_CELLLOOKUPTABLE_CELLLOOKUPTABLE_H_ */
