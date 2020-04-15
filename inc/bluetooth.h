/*
 * bluetooth.h
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#ifndef PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_
#define PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_

#include <stdint.h>
#include <stdbool.h>

#define EMERGENCY_ID "1"
#define NORMAL_ID "2"
#define LOWBATT_ID "3"

void bluetooth_Init(void);
bool_t bluetooth_Read(uint8_t* msg);
void bluetooth_Parser(uint8_t* msg, uint8_t *pId, uint8_t *receiveBuffer);

#endif /* PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_ */
