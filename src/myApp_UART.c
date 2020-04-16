/*
 * myApp_UART.c
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#include "myApp_UART.h"

#define MY_UART UART_USB
#define MY_UART_BAUDRATE 9600
#define MAX_WORDS 4
#define MAX_CHAR 20
/**
 * Array para mapear el ID del mensaje a un texto
 */
static uint8_t idToMessage[MAX_WORDS][MAX_CHAR] = {"Error", "Emergencia", "Normal", "Bateria baja"};

void miApp_UART_Init(void){
	uartConfig( MY_UART, MY_UART_BAUDRATE );
}
void miApp_UART_Send(uint8_t msgId, uint8_t* msg){
	uint8_t messageToSend[100];
	if (msg != NULL) {
		sprintf(messageToSend, "%s: %s\r\n", idToMessage[msgId], msg);
	} else {
		sprintf(messageToSend, "%s\r\n", idToMessage[msgId]);
	}
	uartWriteString(MY_UART,messageToSend);
}
