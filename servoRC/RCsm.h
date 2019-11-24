/*
 * RCsm.h
 *
 *  Created on: 24 nov 2019
 *      Author: massimo
 */

#include <stdint.h>
#include "stm32f7xx_hal.h"

#ifndef RCSM_H_
#define RCSM_H_

#define 	RC_OK		0
#define		NO_TIM		-1
#define		RANGE_PWM	-2

typedef enum{
	base,
	spalla,
	gomito,
	mano,
	polso,
	pinza
} tipoMotore1;

class RCsm {
public:
	RCsm();
	virtual ~RCsm();

	int assignMotor();
	int initRC(TIM_HandleTypeDef *datiPWM, int numCH, tipoMotore1 tipo);
	int go();


public:
	uint16_t 			numCHRc;		/// contiene il numero del canale del motore
	uint16_t 			delta;			/// contiene il valore attuale del PWM
	TIM_HandleTypeDef 	*TIM_PWM;		/// contiene l'indirizzo della struttura che ha i parametri del PWM
	uint32_t			periodo;
	tipoMotore1			motore;
	static uint8_t		numPWM;
};

#endif /* RCSM_H_ */
