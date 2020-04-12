/*
 * debounce.h
 *
 *  Created on: Apr 1, 2020
 *      Author: raul
 */

#ifndef PROGRAMS_SEMAPHORE_INC_DEBOUNCE_H_
#define PROGRAMS_SEMAPHORE_INC_DEBOUNCE_H_

#include "sapi.h"
#include <stdint.h>
#include <stdbool.h>

#define DEBOUNCE_TIME 40

typedef enum{
   UP,
   FALLING,
   DOWN,
   RISING
} debounceState_t;

typedef struct {
	bool_t buttonPressed;
	bool_t buttonReleased;
	gpioMap_t key;
	debounceState_t buttonState;
	delay_t FSMdelay;
} debounceButton_t;

void debounceSM_Init(debounceButton_t *pButton, gpioMap_t key);
void debounceSM_Update(debounceButton_t *pButton);

#endif /* PROGRAMS_SEMAPHORE_INC_DEBOUNCE_H_ */
