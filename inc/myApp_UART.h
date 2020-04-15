/*
 * myApp_UART.h
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#ifndef PROGRAMS_PDM_TPFINAL_INC_MYAPP_UART_C_
#define PROGRAMS_PDM_TPFINAL_INC_MYAPP_UART_C_


#include "sapi.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
/**
 * Funcion miApp_UART_Init
 * @brief Se inicializa puerto serie UART_USB de la EDU_CIAA
 */
void miApp_UART_Init(void);
/**
 * Funcion miApp_UART_Send
 * @brief envia mensaje a a otra terminal  segun el ID del mensaje y el mensaje del usuario
 * @param msgId ID del mensaje a enviar
 * @param msg mensaje del usuario
 */
void miApp_UART_Send(uint8_t msgId, uint8_t* msg);


#endif /* PROGRAMS_PDM_TPFINAL_INC_MYAPP_UART_C_ */
