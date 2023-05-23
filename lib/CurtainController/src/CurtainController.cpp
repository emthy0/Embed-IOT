/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Updated by Jason A. Cox, February 18, 2023.
  Released into the public domain.
*/

#include "Arduino.h"
#include "CurtainController.h"

CurtainController::CurtainController(int pin)
{
  _pin = pin;
  pinMode(_pin, OUTPUT);
}

void CurtainController::setMode(enum CurtainMode mode)
{
  _currentMode = mode;
}

void CurtainController::setLevel(int level)
{
  _currentLevel = level;
}

int CurtainController::getLevel()
{
  return _currentLevel;
}