/*
 * RCsm.cpp
 *
 *  Created on: 24 nov 2019
 *      Author: massimo
 */

#include <RCsm.h>

RCsm::RCsm() {
	// TODO Auto-generated constructor stub
	numCHRc	=	0;		/// contiene il numero del canale del motore
	delta	=	0;			/// contiene il valore attuale del PWM
	TIM_PWM =	NULL;		/// contiene l'indirizzo della struttura che ha i parametri del PWM
	periodo	=	0;
	motore	= 	base;

}

RCsm::~RCsm() {
	// TODO Auto-generated destructor stub
}

