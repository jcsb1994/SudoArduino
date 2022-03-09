#include <Arduino.h>
#include "SudoArduino.h"

#define TIMEOUT_PERIOD_MS (7000)  // period occurs after 7 seconds
unsigned long startTime;
void setup()
{
    Serial.begin(9600);
    startTime = (MAX_ULONG_VALUE - 1000); // simulates a start right before millis() overflow
    Serial.println("Timer starts here");
}

void loop()
{
  delay(200);
  if(isTimeOut(startTime, TIMEOUT_PERIOD_MS)) {
    Serial.println("Timeout reached!");
    while(69);
  }
}