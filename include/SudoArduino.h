//***********************************************************************************
// Copyright 2022 jcsb1994
// Written by jcsb1994
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//***********************************************************************************
//
// Description:
//    This file provides advanced functions with Arduino 
//***********************************************************************************
#ifndef SUDO_ARDUINO_H
#define SUDO_ARDUINO_H

#include <Arduino.h>
#define MAX_ULONG_VALUE (4294967295) 

namespace SudoArduino {

/***************************************************************************/
/*!
    @brief Checks if a start timestamp is older than a timeout period. Immune to millis() overflow.
    @return true if older than timeout period.
*/
/***************************************************************************/
bool isTimeOut(unsigned long &startTime, unsigned long TimeOutPeriod);

}

#endif