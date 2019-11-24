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

typedef enum{
	base,
	spalla,
	gomito,
	mano,
	polso,
	pinza
} tipoMotore;

class RCsm {
public:
	RCsm();
	virtual ~RCsm();

	void initRC();


public:
	uint16_t 			numCHRc;		/// contiene il numero del canale del motore
	uint16_t 			delta;			/// contiene il valore attuale del PWM
	TIM_HandleTypeDef 	*TIM_PWM;		/// contiene l'indirizzo della struttura che ha i parametri del PWM
	uint32_t			periodo;
	tipoMotore			motore;
};

#endif /* RCSM_H_ */
