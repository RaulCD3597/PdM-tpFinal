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

static deviceState_t mainState;
static debounceButton_t patientAttended;

int main(void) {

	boardInit();
	bluetooth_Init();
	miApp_UART_Init();
	deviceSM_Init();
	debounceSM_Init(&patientAttended, TEC1);

	for (;;) {
		deviceSM_Update();
	}

	return 0;
}

void deviceSM_Init(void) {
	mainState = IDLE;
}

void deviceSM_Update(void) {
	uint8_t msg[100] = "";
	uint8_t receiveBuffer[50] = "";
	uint8_t id = 0;
	switch (mainState) {
	case IDLE:
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, OFF);
		gpioWrite(LEDB, OFF);
		if (bluetooth_Read(msg)) {
			delay(50);
			bluetooth_Parser(msg, &id, receiveBuffer);
			switch (id) {
			case EMERGENCY_BT:
				mainState = EMERGENCY;
				miApp_UART_Send(id, receiveBuffer);
				break;
			case NORMAL_BT:
				mainState = NORMAL;
				miApp_UART_Send(id, receiveBuffer);
				break;
			case LOWBATT_BT:
				miApp_UART_Send(id, receiveBuffer);
				mainState = LOW_BATT;
				break;
			default:
				break;
			}
		}
		break;
	case EMERGENCY:
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, ON);
		gpioWrite(LEDB, OFF);
		debounceSM_Update(&patientAttended);
		if (bluetooth_Read(msg)) {
			delay(50);
			bluetooth_Parser(msg, &id, receiveBuffer);
			if (id == LOWBATT_BT) {
				mainState = EM_LOW_BATT;
				miApp_UART_Send(id, receiveBuffer);
			}
		}
		if (patientAttended.buttonReleased) {
			mainState = IDLE;
		}
		break;
	case NORMAL:
		gpioWrite(LED1, ON);
		gpioWrite(LED2, OFF);
		gpioWrite(LEDB, OFF);
		debounceSM_Update(&patientAttended);
		if (bluetooth_Read(msg)) {
			delay(50);
			bluetooth_Parser(msg, &id, receiveBuffer);
			if (id == LOWBATT_BT) {
				mainState = NOR_LOW_BATT;
				miApp_UART_Send(id, receiveBuffer);
			} else if (id == EMERGENCY_BT) {
				mainState = EMERGENCY;
				miApp_UART_Send(id, receiveBuffer);
			}
		}
		if (patientAttended.buttonReleased) {
			mainState = IDLE;
		}
		break;
	case LOW_BATT:
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, OFF);
		gpioWrite(LEDB, ON);
		debounceSM_Update(&patientAttended);
		if (bluetooth_Read(msg)) {
			delay(50);
			bluetooth_Parser(msg, &id, receiveBuffer);
			if (id == NORMAL_BT) {
				mainState = NOR_LOW_BATT;
				miApp_UART_Send(id, receiveBuffer);
			} else if (id == EMERGENCY_BT) {
				mainState = EM_LOW_BATT;
				miApp_UART_Send(id, receiveBuffer);
			}
		}
		if (patientAttended.buttonReleased) {
			mainState = IDLE;
		}
		break;
	case EM_LOW_BATT:
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, ON);
		gpioWrite(LEDB, ON);
		debounceSM_Update(&patientAttended);
		if (patientAttended.buttonReleased) {
			mainState = IDLE;
		}
		break;
	case NOR_LOW_BATT:
		gpioWrite(LED1, ON);
		gpioWrite(LED2, OFF);
		gpioWrite(LEDB, ON);
		debounceSM_Update(&patientAttended);
		if (bluetooth_Read(msg)) {
			delay(50);
			bluetooth_Parser(msg, &id, receiveBuffer);
			if (id == EMERGENCY_BT) {
				mainState = EM_LOW_BATT;
				miApp_UART_Send(id, receiveBuffer);
			}
		}
		if (patientAttended.buttonReleased) {
			mainState = IDLE;
		}
		break;
	default:
		deviceSM_Init();
		break;
	}
}
