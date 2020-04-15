/*
 * myApp.c
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#include "sapi.h"
#include "bluetooth.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {

	boardInit();
	bluetooth_Init();
	uartConfig( UART_USB, 9600 );
	uint8_t msg[256] = "";
	uint8_t numOfChar = 0;

	for (;;) {
		if(bluetooth_Read(msg)){
			uartWriteString(UART_USB, msg);
		}
	}

	return 0;
}

