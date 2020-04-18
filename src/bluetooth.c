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
	delay_t mydelay;
	uint8_t receiveByte;
	uint8_t index = 0;
	delayInit(&mydelay, BT_MAX_WAIT_TIME);
	bool_t retVal = FALSE;
	memset(receiveBuffer, 0, sizeof(receiveBuffer));
	while (!(delayRead(&mydelay))) {
		if (uartReadByte( BLUETOOTH, &receiveByte)) {
			receiveBuffer[index] = receiveByte;
			index++;
			retVal = TRUE;
		}
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
