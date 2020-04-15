/*
 * myApp_UART.c
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#include "myApp_UART.h"

#define MY_UART UART_USB
#define MY_UART_BAUDRATE 9600
/**
 * Array para mapear el ID del mensaje a un texto
 * al mapear se debe restar en una unidad ya que lo IDs
 * tienen un rango de 1 a 3 y los indices del array comienzan
 * en cero
 */
static uint8_t **idToMessage = {"Emergencia", "Normal", "Bateria baja"};

void miApp_UART_Init(void){
	uartConfig( MY_UART, MY_UART_BAUDRATE );
}
void miApp_UART_Send(uint8_t msgId, uint8_t* msg){
	uint8_t messageToSend[100];
	sprintf(messageToSend,"%s: %s\r\n", idToMessage[msgId - 1], msg);
	uartWriteString(MY_UART,messageToSend);
}
