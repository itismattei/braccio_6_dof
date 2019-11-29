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


//!  Classe che implementa e gestisce i servomotori .
/*!
  Questa classe si occupa di gestire i servomotori dei 6 gradi di liberta' del
  braccio. Una variabile statica indica il numero di servi che sono attualemente gestiti.
*/



    //! A normal member taking two arguments and returning an integer value.
    /*!
      \param a an integer argument.
      \param s a constant character pointer.
      \return The test results
      \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
    */
    int testMe(int a,const char *s);

    //! A pure virtual member.
    /*!
      \sa testMe()
      \param c1 the first argument.
      \param c2 the second argument.
    */
    virtual void testMeToo(char c1,char c2) = 0;

    //! A public variable.
    /*!
      Details.
    */
    int publicVar;

    //! A function variable.
    /*!
      Details.
    */
    int (*handler)(int a,int b);
};

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

	//! Metodo go(): trasferisce il valore del delta all'interno del registro della CPU
	/*!
	  \param nessuno
	  \return codice di errore
	*/
	int go();


public:
	uint16_t 			numCHRc;		///< contiene il numero del canale del motore
	uint16_t 			delta;			///< contiene il valore attuale del PWM
	TIM_HandleTypeDef 	*TIM_PWM;		///< contiene l'indirizzo della struttura che ha i parametri del PWM
	uint32_t			periodo;		///< periodo del PWM
	tipoMotore1			motore;
	static uint8_t		numPWM;
};

#endif /* RCSM_H_ */
