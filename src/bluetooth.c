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
#define MSG_SPC_TO_CONTENT 3
#define MSG_SPC_TO_END 4
#define BT_MAX_WAIT_TIME 100
/**
 * Funcion get_ID
 * @brief Obtiene el ID del mensaje
 * @param msg mensaje del que se quiere extraer el ID
 * @param pID puntero a la variable donde se guardara el ID
 */
static void get_ID(uint8_t* msg, uint8_t *pId);
/**
 * Funcion get_Msg
 * @brief Obtiene el mensaje que describe la necesida del paciente del mensaje recibido po BT
 * @param msg mensaje del que se quiere extraer el mensaje del paciente
 * @param receiveBuffer variable donde se guardara el mensaje del paciente
 */
static void get_Msg(uint8_t* msg, uint8_t *receiveBuffer);

void bluetooth_Init(void) {
	uartConfig( BLUETOOTH, BT_BAUDRATE);
}

bool_t bluetooth_Read(uint8_t *msg) {
	delay_t mydelay;
	uint8_t receiveByte;
	uint8_t index = 0;
	delayInit(&mydelay, BT_MAX_WAIT_TIME);
	bool_t retVal = FALSE;
	memset(msg, 0, sizeof(msg));
	while (!(delayRead(&mydelay))) {
		if (uartReadByte( BLUETOOTH, &receiveByte)) {
			msg[index] = receiveByte;
			index++;
			retVal = TRUE;
		}
	}
	return retVal;
}
/**
 * Se espera que los mensajes que llegan esten en formato json segun la
 * siguiente plantilla:
 * 		{"id": ID, "msg": "mensaje del paciente"}
 */
void bluetooth_Parser(uint8_t* msg, uint8_t *pId, uint8_t *receiveBuffer) {
	get_ID(msg, pId);
	get_Msg(msg, receiveBuffer);
}

static void get_ID(uint8_t* msg, uint8_t *pId) {
	uint8_t *search = strstr(msg, ID_STRING);
	if (search != NULL) {
		search = strstr(search, SEPARATOR);
		search += SPC_TO_CONTENT;
		if (!strncmp(search, EMERGENCY_ID, 1)) {
			*pId = EMERGENCY_BT;
		} else if ((!strncmp(search, NORMAL_ID, 1))) {
			*pId = NORMAL_BT;
		} else if ((!strncmp(search, LOWBATT_ID, 1))) {
			*pId = LOWBATT_BT;
		} else {
			*pId = NO_ID;
		}
	}
}

static void get_Msg(uint8_t* msg, uint8_t *receiveBuffer) {
	uint8_t *search = strstr(msg, MSG_STRING);
	if (search != NULL) {
		search = strstr(search, SEPARATOR);
		search += MSG_SPC_TO_CONTENT;
		uint8_t length = strlen(search);
		strncpy(receiveBuffer, search, length - MSG_SPC_TO_END);
	} else {
		memset(receiveBuffer, 0, sizeof(receiveBuffer));
	}
}
