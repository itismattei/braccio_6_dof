/*
 * joystick1->c
 *
 *  Created on: 19 mar 2019
 *      Author: s_rvrndr02a27g479k
 */
#include "math.h"
#include <stdbool.h>
#include "main.h"
#include "stm32f7xx_hal.h"

#include "joystick.h"


void joystickINIT ( joystick *newJoy, uint8_t valueX, uint8_t valueY, uint8_t valueSw, int zeroX, int zeroY ){
  newJoy->pinVRx = valueX;
  newJoy->pinVRy = valueY;
  newJoy->pinSW= valueSw;
  newJoy->zeroX= zeroX;
  newJoy->zeroY= zeroY;
//  pinMode( newJoy->pinVRx, INPUT);
//  pinMode( newJoy->pinVRy, INPUT);
//  pinMode( newJoy->pinSw,INPUT_PULLUP);
};

bool push ( joystick *newJoy ){
  bool state;
  if(HAL_GPIO_ReadPin(GPIOC, newJoy->pinSW )== GPIO_PIN_SET)
    state = false;
  else
    state = true;
  return state;
};

int getDegree( joystick *newJoy ){
  int valVRX  = 0; ///HAL_GPIO_ReadPin(newJoy->pinVRx)-newJoy->zeroX;
  int valVRY  = 0; ///HAL_GPIO_ReadPin(newJoy->pinVRy)-newJoy->zeroY;
  int radiant = atan(valVRX/valVRY);
  int degree  = (radiant*180)/ M_PI;
  if(newJoy->pinVRx<0 && newJoy->pinVRy>0) degree=degree+180;//si trova nel secondo quadrante
  if(newJoy->pinVRx<0 && newJoy->pinVRy<0) degree=degree+180;//si trova nel terzo quadrante
  if(newJoy->pinVRx>0 && newJoy->pinVRy<0) degree=degree+360;//si trova nel quarto quadrante
  return degree;
};

verse getVerseX ( joystick * newJoy ){
  verse way;
  if ( newJoy->pinVRx == 0 ) way = NO;
  if ( newJoy->pinVRx >  0 ) way = CV;
  if ( newJoy->pinVRx <  0 ) way = CCV;
  return way;
};

verse getVerseY ( joystick* newJoy ){
  verse way;
  if ( newJoy->pinVRy == 0 ) way = NO;
  if ( newJoy->pinVRy >  0 ) way = CV;
  if ( newJoy->pinVRy <  0 ) way = CCV;
  return way;
};


