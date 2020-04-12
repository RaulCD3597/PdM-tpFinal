/*
 * debounce.c
 *
 *  Created on: Apr 1, 2020
 *      Author: raul
 */
#include "debounce.h"
#include "sapi.h"
#include <stdint.h>
#include <stdbool.h>



void debounceSM_Init(debounceButton_t *pButton, gpioMap_t key){
	pButton->buttonPressed = FALSE;
	pButton->buttonReleased = TRUE;
	pButton->key = key;
	pButton->buttonState = UP;
}

void debounceSM_Update(debounceButton_t *pButton){
	switch (pButton->buttonState) {
	case UP:
		pButton->buttonPressed = FALSE;
		pButton->buttonReleased = TRUE;
		if (!gpioRead(pButton->key)){
			delayInit(&pButton->FSMdelay, DEBOUNCE_TIME);
			pButton->buttonState = FALLING;
		}
		break;
	case FALLING:
		pButton->buttonPressed = FALSE;
		pButton->buttonReleased = TRUE;
		if (delayRead(&pButton->FSMdelay)){
			if (!gpioRead(pButton->key)) {
				pButton->buttonState = DOWN;
			} else {
				pButton->buttonState = UP;
			}
		}
		break;
	case DOWN:
		pButton->buttonPressed = TRUE;
		pButton->buttonReleased = FALSE;
		if (gpioRead(pButton->key)){
			delayInit(&pButton->FSMdelay, DEBOUNCE_TIME);
			pButton->buttonState = RISING;
		}
		break;
	case RISING:
		pButton->buttonPressed = TRUE;
		pButton->buttonReleased = FALSE;
		if (delayRead(&pButton->FSMdelay)) {
			if (!gpioRead(pButton->key)) {
			} else {
				pButton->buttonState = UP;
			}
		}
		break;
	default:
		debounceSM_Init(pButton, pButton->key);
		break;
	}
}
