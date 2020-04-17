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

#define BLUETOOTH UART_232
#define BT_BAUDRATE 9600

void bluetooth_Init(void);
bool_t bluetooth_Read(char* receiveBuffer, uint8_t* receiveBufferSize);
uint8_t bluetooth_Parser(uint8_t* msg);

#endif /* PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_ */
