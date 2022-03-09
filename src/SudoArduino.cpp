#include "SudoArduino.h"


#define DEBUG_SUDO_ARDUINO 0
#if DEBUG_SUDO_ARDUINO
#define PRINT_SUDO_ARDUINO(msg) Serial.println(msg)
#else
#define PRINT_SUDO_ARDUINO(msg) 
#endif

bool SudoArduino::isTimeOut(unsigned long &startTime, unsigned long TimeOutPeriod) {
    unsigned long gap;
    PRINT_SUDO_ARDUINO("Start time: " + String(startTime));
    if (millis() < startTime) {   // in case of overflow
      PRINT_SUDO_ARDUINO("Millis Overflow");
      gap = (MAX_ULONG_VALUE - startTime) + millis() + 1;
    } else {
      PRINT_SUDO_ARDUINO("Calculating time between now and timer start");
      gap = millis() - startTime;
    }  
    if (gap >= TimeOutPeriod) {
      PRINT_SUDO_ARDUINO(String(gap) + " is bigger than timeout period " + String(TimeOutPeriod));
      return true;
    } else {
      PRINT_SUDO_ARDUINO("Not reached");
      return 0;
    }
}
