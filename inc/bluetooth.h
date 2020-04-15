/*
 * bluetooth.h
 *
 *  Created on: Apr 12, 2020
 *      Author: raulcamacho
 */

#ifndef PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_
#define PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_

#include <stdint.h>
#include <stdbool.h>

#define EMERGENCY_ID "1"
#define NORMAL_ID "2"
#define LOWBATT_ID "3"

/**
 * @brief enum para asignar un valor al tipo de ID de mensaje
 */
enum{
	NO_ID = 0,
	EMERGENCY,
	NORMAL,
	LOWBATT
};
/**
 * funcion bluetooth_Init
 * @brief  Inicializa puerto serial 232 de la EDUCIAA para uso de bluetooth
 */
void bluetooth_Init(void);
/**
 * funcion bluetooth_Read
 * @brief lee el mensaje recibido por el modulo bluetooth y guarda el mensaje en msg
 * @param msg variable donde se guardara el mensaje recibido
 * @retrun true si se recibio un mensaje por bluetooth, false caso contrario
 */
bool_t bluetooth_Read(uint8_t* msg);
/**
 * fuincion bluetooth_Parser
 * @brief interpreta el mensaje bluetooth guardando el id y el contenido del mensaje
 * @param msg cadena que se desea interpretear
 * @param pId puntero a la variable donde se guardara el id del mensaje
 * @param receiveBuffer variable donde se guardara el mensaje que describe la situacion del paciente
 */
void bluetooth_Parser(uint8_t* msg, uint8_t *pId, uint8_t *receiveBuffer);

#endif /* PROGRAMS_PDM_TPFINAL_INC_BLUETOOTH_H_ */
