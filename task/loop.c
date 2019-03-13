/*
 * loop.c
 *
 *  Created on: 07 feb 2019
 *      Author: massimo
 */

#include "stm32f7xx_hal.h"

extern volatile uint32_t TICK, MS100, S1;
#define		TIC500		50

void loop(void){

	  if (TICK >= TIC500){
		  ///lampeggio ogni 500 ms.
		  HAL_GPIO_TogglePin(GPIOB, LD1_Pin|LD2_Pin|LD3_Pin);
		  TICK = 0;
	  }

}
