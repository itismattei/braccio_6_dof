/*
 * loop.c
 *
 *  Created on: 07 feb 2019
 *      Author: massimo
 */

#include "stm32f7xx_hal.h"
#include <stdbool.h>
#include "servomotoreRC.h"

extern volatile uint32_t TICK, MS100, S1;
extern servoRC RC[];
extern uint32_t buffer[];
extern bool ADupdate;
extern ADC_HandleTypeDef hadc3;
#define		TIC500		50

volatile int JY1_X;
volatile int JY1_Y;
volatile int JY1_SW;
volatile int JY2_X;
volatile int JY2_Y;
volatile int JY2_SW;

volatile bool state1 = false;
volatile bool state2 = false;

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
	 /* for(float i=0; i < 0.140; i=i+0.001){
		  RC[5].delta = (uint32_t) RC[5].periodo *i;
		 goRC(&RC[5]);
		 HAL_Delay(1000);
		 printf("%d\n", RC[5].delta);
	  }*/
	  JY1_X = buffer[0]; //base
	  JY1_Y = buffer[1]; //spalla
	  JY1_SW= buffer[2];
	  JY2_X = buffer[3]; //mano //gomito
	  JY2_Y = buffer[4]; //polso //pinza
	  JY2_SW= buffer[5];
	  volatile int base,spalla,mano,gomito,polso,pinza;
	  if( JY1_SW > 4000 || JY2_SW < 4000 ){
		  state1 = true;
		  state2 = false;
	  }
	  if( JY2_SW > 4000 || JY1_SW < 4000 ){
		  state2 = true;
		  state1 = false;
	  }
	  if( state1 == true ){
		  base=JY1_X*0.13/4096;//proporazione cinese che lega potenziometro e valori massimi di PWM
		  spalla=JY1_Y*0.11/4096;
		  gomito = JY2_X * 0.127/4096;
		  mano = JY2_Y * 0.128/4096;
	  }

	  if( state2 == true ){

		  polso = JY2_X * 0.1245/4096;
		  pinza = JY2_Y * 0.073/4096;
	  }
	  // verifica se occorre aggiornare le letture dei convertitori
	  if (ADupdate == false)
		  /// aggiorna ogni volta che il dato e' usato, la lettura dei convertitori AD
		  /// La funzione callback riporta ADupdate a true
		  HAL_ADC_Start_DMA(&hadc3, buffer, 6);
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
