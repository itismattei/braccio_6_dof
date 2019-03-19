/*
 * joystick.h
 *
 *  Created on: 19 mar 2019
 *      Author: s_rvrndr02a27g479k
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_



#include "math.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct __joystick {

	uint16_t pinVRx;
    uint16_t pinVRy;
    uint16_t pinSW;
    int  zeroX; //valore asse x quando il potenziomentro è in posizione (0,0)
    int  zeroY; //valore asse y quando il potenziomentro è in posizione (0,0)

} joystick;

typedef enum   { CV , CCV , NO } verse;

	void joystickINIT (joystick *, uint8_t VRx, uint8_t VRy, uint8_t SW, int valX, int valY);
 // void initialize (void);
    int  getDegree  ( joystick *);
    bool push       ( joystick *);
    verse getVerseX ( joystick *);
    verse getVerseY ( joystick *);


#endif /* JOYSTICK_H_ */
