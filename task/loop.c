/*
 * loop.c
 *
 *  Created on: 07 feb 2019
 *      Author: massimo
 */

#include "stm32f7xx_hal.h"
#include "servomotoreRC.h"

extern volatile uint32_t TICK, MS100, S1;
extern servoRC RC[];

#define		TIC500		50

void loop(void){

	  if (TICK >= TIC500){
		  ///lampeggio ogni 500 ms.
		  HAL_GPIO_TogglePin(GPIOB, LD1_Pin|LD2_Pin|LD3_Pin);
		  TICK = 0;
	  }

	  //RC[3].delta = (uint32_t) RC[3].periodo *0.05;
	  //goRC(&RC[3]);
	  //RC[5].delta = (uint32_t) RC[5].periodo *0.05;
	  //goRC(&RC[5]);
	  //RC[0].delta = (uint32_t) RC[0].periodo *0.075;
	  //goRC(&RC[0]);
	  RC[2].delta = (uint32_t) RC[2].periodo *0.075;
	  goRC(&RC[2]);
}


///
/// imposta i motori in posizione centrale
/// il braccio e' verticale
void setup(){
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	  RC[0].delta = (uint32_t) RC[0].periodo *0.075;
	  RC[1].delta = (uint32_t) RC[1].periodo *0.075;
	  RC[2].delta = (uint32_t) RC[2].periodo *0.075;
	  RC[3].delta = (uint32_t) RC[3].periodo *0.075;
	  RC[4].delta = (uint32_t) RC[4].periodo *0.075;
	  RC[5].delta = (uint32_t) RC[5].periodo *0.075;
	  for (int i = 0; i < 6; i++)
	  	 //! le strutture dati sono impostate e i PWM vengono avviati
	  	 goRC(&RC[i]);
}
