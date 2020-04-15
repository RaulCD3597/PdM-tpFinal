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

#define ID_STRING "id"
#define MSG_STRING "msg"
#define SEPARATOR ":"
#define BLUETOOTH UART_232
#define BT_BAUDRATE 9600
#define SPC_TO_CONTENT 2

enum{
	NO_ID = 0,
	EMERGENCY,
	NORMAL,
	LOWBATT
};

void get_ID(uint8_t* msg, uint8_t *pId);
void get_Msg(uint8_t* msg, uint8_t *receiveBuffer);

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

void bluetooth_Parser(uint8_t* msg, uint8_t *pId, uint8_t *receiveBuffer) {
	get_ID(msg, pId);
	get_Msg(msg, receiveBuffer);
}

void get_ID(uint8_t* msg, uint8_t *pId) {
	uint8_t *search = strstr(msg, ID_STRING);
	if (search != NULL) {
		search = strstr(search, SEPARATOR);
		search += SPC_TO_CONTENT;
		if (!strncmp(search, EMERGENCY_ID, 1)) {
			*pId = EMERGENCY;
		} else if ((!strncmp(search, NORMAL_ID, 1))) {
			*pId = NORMAL;
		} else if ((!strncmp(search, LOWBATT_ID, 1))) {
			*pId = LOWBATT;
		} else {
			*pId = NO_ID;
		}
	}
}

void get_Msg(uint8_t* msg, uint8_t *receiveBuffer) {
	uint8_t *search = strstr(msg, MSG_STRING);
	if (search != NULL) {
		search = strstr(search, SEPARATOR);
		search += SPC_TO_CONTENT;
		uint8_t length = strlen(search);
		strncpy(receiveBuffer,search,length);
	}
}
