#include <Arduino.h>
#include "SudoArduino.h"

#define TIMEOUT_PERIOD_MS (7000)  // period occurs after 7 seconds
void setup()
{
    Serial.begin(9600);
    Serial.println("Hello");
}

void loop()
{
    if(isTimeOut())
}