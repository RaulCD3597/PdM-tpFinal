/*
 * bluetooth.c
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#include "sapi.h"
#include <string.h>
#include "bluetooth.h"
#include <stdint.h>
#include <stdbool.h>

#define BT_MAX_WAIT_TIME 200

typedef enum {
	BT_RECEIVING, BT_TIME_OUT
} btState_t;

typedef struct {
	uint8_t index;
	btState_t state;
	delay_t btDelay;
} btDevice_t;

bool_t bluetooth_update(btDevice_t *pbtDevice, char* receiveBuffer,
		uint8_t* receiveBufferSize);

void bluetooth_Init(void) {
	uartConfig(BLUETOOTH, BT_BAUDRATE);
}

bool_t bluetooth_Read(char* receiveBuffer, uint8_t* receiveBufferSize) {
	btDevice_t myBT;
	myBT.state = BT_RECEIVING;
	delayInit(&(myBT.btDelay), BT_MAX_WAIT_TIME);
	myBT.index = 0;
	bool_t retVal = FALSE;
	while (myBT.state == BT_RECEIVING) {
		retVal = bluetooth_update(&myBT, receiveBuffer, receiveBufferSize);
	}
	return retVal;
}

bool_t bluetooth_update(btDevice_t *pbtDevice, char* receiveBuffer,
		uint8_t* receiveBufferSize) {

	uint8_t receiveByte;
	if (uartReadByte( BLUETOOTH, &receiveByte)) {
		if (pbtDevice->index < *receiveBufferSize) {
			receiveBuffer[(pbtDevice->index)] = receiveByte;
			(pbtDevice->index)++;
		} else {
			pbtDevice->state = BT_TIME_OUT;
			if (pbtDevice->index > 0) {
				return TRUE;
			}
		}
		if (delayRead(&(pbtDevice->btDelay))) {
			pbtDevice->state = BT_TIME_OUT;
			if (pbtDevice->index > 0) {
				return TRUE;
			}
		}
	}
	return FALSE;
}
