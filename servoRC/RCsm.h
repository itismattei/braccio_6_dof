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

const float taraturaMAxPWM[6]{
	/*volatile float MAX_base = */	0.130,
	/*volatile float MAX_spalla =*/ 0.110,
	/*volatile float MAX_gomito =*/ 0.127,
	/*volatile float MAX_polso = */	0.1245,
	/*volatile float MAX_mano = */	0.128,
	/*volatile float MAX_pinza = */	0.073
};


typedef enum{
	base,
	spalla,
	gomito,
	mano,
	polso,
	pinza
} tipoMotore1;


//!  Classe che implementa e gestisce i servomotori .
/*!
  Questa classe si occupa di gestire i servomotori dei 6 gradi di liberta' del
  braccio. Una variabile statica indica il numero di servi che sono attualemente gestiti.
*/

class RCsm {
public:
    //! A constructor.
    /*!
      A more elaborate description of the constructor.
    */
	RCsm();
	//! A destructor.
	/*!
	  A more elaborate description of the destructor.
	*/
	virtual ~RCsm();

	int assignMotor();

	//! Metodo initRC che richiede 3 parametri di ingresso e restituisce un intero.
	/*!
	  \param *datiPWM: struttura dati che gestisce i registri della CPU.
	  \param numCH Numer del canale del motore.
	  \return codice di errore
	  \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
	*/
	int initRC(TIM_HandleTypeDef *datiPWM, int numCH, tipoMotore1 tipo);

	//! Metodo setPWM: imposta il delta del PWM
	/*!
	  \param valore del PWM in percentuale. Il valore e' compreso tra 5% e 10%
	  \return codice di errore
	*/
	inline int setPWM(float d) {delta = (uint32_t) periodo * d; pwm = d; return RC_OK;}
	RCsm& setPWM(void){ delta = (uint32_t) periodo * pwm; return *this; }

	//! Metodo go(): trasferisce il valore del delta all'interno del registro della CPU
	/*!
	  \param nessuno
	  \return codice di errore
	*/
	int go(void);


public:
	uint16_t 			numCHRc;		///< contiene il numero del canale del motore
	uint16_t 			delta;			///< contiene il valore attuale del PWM
										///< per questi motori va dal 5% al 10%
										///< del valore del periodo
	float				pwm;			///< contiene il valore decimale del PWM
	float				MAX;			///< valore massimo ammesso dopo la taratura
	float				MIN;			///< valore minimo dopo la taratura
	TIM_HandleTypeDef 	*TIM_PWM;		///< contiene l'indirizzo della struttura che ha i parametri del PWM
	uint32_t			periodo;		///< periodo del PWM di valore pari a 20ms
										///< che in questo caso vale 2000
	tipoMotore1			motore;			///< indica di quale motore si tratta
	static uint8_t		numPWM;			///< variabile statica che indica il numero di motori registrati
};

#endif /* RCSM_H_ */
