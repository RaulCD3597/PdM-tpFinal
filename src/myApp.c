/*
 * myApp.c
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#include "sapi.h"
#include "myApp.h"
#include "bluetooth.h"
#include "myApp_UART.h"
#include "debounce.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {

	boardInit();
	bluetooth_Init();
	miApp_UART_Init();
	static debounceButton_t patientSttended;
	debounceSM_Init(&patientSttended, TEC1);
	uint8_t msg[100] = "";
	uint8_t receiveBuffer[50] = "";

	for (;;) {
		debounceSM_Update(&patientSttended);
		if (patientSttended.buttonReleased == TRUE){
			miApp_UART_Send(1, NULL);
		}
		if (bluetooth_Read(msg)) {
			delay(50);
			uint8_t id = 0;
			bluetooth_Parser(msg, &id, receiveBuffer);
			if (id == 1) {
				gpioWrite(LED1, OFF);
				gpioWrite(LED2, ON);
				gpioWrite(LEDB, OFF);
			} else if (id == 2) {
				gpioWrite(LED1, ON);
				gpioWrite(LED2, OFF);
				gpioWrite(LEDB, OFF);
			}else if (id == 3) {
				gpioWrite(LED1, OFF);
				gpioWrite(LED2, OFF);
				gpioWrite(LEDB, ON);
			}  else {
				gpioWrite(LED1, OFF);
				gpioWrite(LED2, OFF);
				gpioWrite(LEDB, OFF);
			}
			memset(msg, 0, sizeof(msg));
		}
	}

	return 0;
}

