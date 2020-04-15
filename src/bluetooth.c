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

void bluetooth_Init(void){
	uartConfig( BLUETOOTH, BT_BAUDRATE );
}

bool_t bluetooth_Read(uint8_t *msg){
	uint8_t data = 0;
	uint8_t number = 0;
	bool_t retVal = FALSE;
	memset(msg, 0, sizeof(msg));
	while (uartReadByte(BLUETOOTH, &data) && (data != '\r') && (data != '\n')) {
		msg[number] = data;
		number++;
		retVal = TRUE;
	}
	return retVal;
}
