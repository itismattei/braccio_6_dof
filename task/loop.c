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

volatile bool state1 = true;
volatile bool state2 = false;

volatile bool button1_old = true;
volatile bool button2_old = true;

#define min 0.040

volatile float PWM_base = 0.075;
volatile float PWM_spalla = 0.075;
volatile float PWM_gomito = 0.075;
volatile float PWM_polso = 0.075;
volatile float PWM_mano = 0.075;
volatile float PWM_pinza = 0.075;

volatile float MAX_base = 0.130;
volatile float MAX_spalla = 0.110;
volatile float MAX_gomito = 0.127;
volatile float MAX_polso = 0.1245;
volatile float MAX_mano = 0.128;
volatile float MAX_pinza = 0.073;

// memoria
volatile float pos[200][6];
volatile int mem = 0;
volatile bool button3 = false;
volatile bool button3_old = true;

volatile bool programmation = false;
volatile bool execution = false;

volatile bool exit_old;
volatile bool exit_new;

void loop(void){

	if (TICK >= TIC500){
	///lampeggio ogni 500 ms.
	HAL_GPIO_TogglePin(GPIOB, LD1_Pin|LD2_Pin|LD3_Pin);
	TICK = 0;
	}

	// verifica se occorre aggiornare le letture dei convertitori
	if (ADupdate == false)
	/// aggiorna ogni volta che il dato e' usato, la lettura dei convertitori AD
	/// La funzione callback riporta ADupdate a true
	HAL_ADC_Start_DMA(&hadc3, buffer, 6);
	/*for(float i=0; i < 0.140; i=i+0.001){
	RC[1].delta = (uint32_t) RC[1].periodo *i;
	goRC(&RC[1]);
	HAL_Delay(1000);
	printf("%d\n", RC[1].delta);
	}*/

	if(execution == false){

		JY1_X = buffer[0]; //base
		JY1_Y = buffer[1]; //spalla
		JY1_SW= buffer[2];
		JY2_X = buffer[3]; //mano //gomito
		JY2_Y = buffer[4]; //polso //pinza
		JY2_SW= buffer[5];

		int a = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10);
		if( button2_old == false && a == GPIO_PIN_RESET ){
			button2_old = true;
			if( state1 == true ){
				state1 = false;
				state2 = true;
			}
			else{
				state2 = false;
				state1 = true;
			}
		}
		else
			button2_old = false;

		button3_old = button3;
		button3 = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_12);
		if(button3 == true && button3_old == false){
			if(programmation == true){
				programmation = false;
				execution = true;
			}
			else if(programmation == false){
				programmation = true;
				execution = false;
			}
		}

		if( state1 == true){
			if( JY1_X > 3000 && PWM_base < MAX_base )
				PWM_base = PWM_base + 0.001;
			if( JY1_X < 1500 && PWM_base > min )
				PWM_base = PWM_base - 0.001;
			if( JY1_Y > 3000 && PWM_spalla > min )
				PWM_spalla = PWM_spalla - 0.001;
			if( JY1_Y < 1500 && PWM_spalla < MAX_spalla )
				PWM_spalla = PWM_spalla + 0.001;
			if( JY2_X > 3500 && PWM_gomito < MAX_gomito )
				PWM_gomito = PWM_gomito + 0.001;
			if( JY2_X < 1500 && PWM_gomito > min )
				PWM_gomito = PWM_gomito - 0.001;
			if( JY2_Y > 3500 && PWM_mano > min )
				PWM_mano = PWM_mano - 0.001;
			if( JY2_Y < 1500 && PWM_mano < MAX_mano )
				PWM_mano = PWM_mano + 0.001;

			if(programmation == true){
				pos[mem][0] = PWM_base;
				pos[mem][1] = PWM_gomito;
				pos[mem][2] = PWM_spalla;
				pos[mem][3] = PWM_mano;
			}

			HAL_Delay(45);

		}
		else if( state2 == true){

			if( JY2_X > 3500 && PWM_pinza < MAX_pinza )
				PWM_pinza = PWM_pinza + 0.001;
			if( JY2_X < 1500 && PWM_pinza > min )
				PWM_pinza = PWM_pinza - 0.001;
			if( JY2_Y > 3500 && PWM_polso > min )
				PWM_polso = PWM_polso - 0.001;
			if( JY2_Y < 1500 && PWM_polso < MAX_polso )
				PWM_polso = PWM_polso + 0.001;

			if(programmation == true){
				pos[mem][4] = PWM_pinza;
				pos[mem][5] = PWM_polso;
			}

			HAL_Delay(30);
		}

		RC[0].delta = (uint32_t) RC[0].periodo * PWM_base;
		goRC(&RC[0]);
		RC[1].delta = (uint32_t) RC[1].periodo * PWM_spalla;
		goRC(&RC[1]);
		RC[2].delta = (uint32_t) RC[2].periodo * PWM_gomito;
		goRC(&RC[2]);
		RC[3].delta = (uint32_t) RC[3].periodo * PWM_mano;
		goRC(&RC[3]);
		RC[4].delta = (uint32_t) RC[4].periodo * PWM_polso;
		goRC(&RC[4]);
		RC[5].delta = (uint32_t) RC[5].periodo * PWM_pinza;
		goRC(&RC[5]);

		if(mem >= 200 && programmation == true){
			execution = true;
			state1 = false;
			state2 = false;
		}

		else if(programmation == true)
			mem = mem + 1;
	}


	else if(execution == true){
		for(int d = (mem - 1); d >= 0; d--){
			RC[0].delta = (uint32_t) RC[0].periodo * pos[d][0];
			goRC(&RC[0]);
			RC[1].delta = (uint32_t) RC[1].periodo * pos[d][2];
			goRC(&RC[1]);
			RC[2].delta = (uint32_t) RC[2].periodo * pos[d][1];
			goRC(&RC[2]);
			RC[3].delta = (uint32_t) RC[3].periodo * pos[d][3];
			goRC(&RC[3]);
			RC[4].delta = (uint32_t) RC[4].periodo * pos[d][4];
			goRC(&RC[4]);
			RC[5].delta = (uint32_t) RC[5].periodo * pos[d][5];
			goRC(&RC[5]);

			HAL_Delay(30);
		}
		for(int d = 0; d <= (mem - 1); d++){
			RC[0].delta = (uint32_t) RC[0].periodo * pos[d][0];
			goRC(&RC[0]);
			RC[1].delta = (uint32_t) RC[1].periodo * pos[d][2];
			goRC(&RC[1]);
			RC[2].delta = (uint32_t) RC[2].periodo * pos[d][1];
			goRC(&RC[2]);
			RC[3].delta = (uint32_t) RC[3].periodo * pos[d][3];
			goRC(&RC[3]);
			RC[4].delta = (uint32_t) RC[4].periodo * pos[d][4];
			goRC(&RC[4]);
			RC[5].delta = (uint32_t) RC[5].periodo * pos[d][5];
			goRC(&RC[5]);

			HAL_Delay(30);
		}
		exit_old = exit_new;
		exit_new = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
		if(exit_new == true && exit_old == false){
			execution = false;
			state1 = true;
			mem = 0;
			for(int d = 0; d <= mem -1; d++){
				pos[d][0] = ' ';
				pos[d][2] = ' ';
				pos[d][1] = ' ';
				pos[d][3] = ' ';
				pos[d][4] = ' ';
				pos[d][5] = ' ';
			}
		}
	}
}
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
