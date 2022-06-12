#include "SudoArduino.h"


#define DEBUG_SUDO_ARDUINO 1
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
      PRINT_SUDO_ARDUINO("Calculating time between now and timer start: " + String(millis()) + " " + String(startTime));
      gap = millis() - startTime;
    }  
    if (gap >= TimeOutPeriod) {
      PRINT_SUDO_ARDUINO(String(gap) + " is bigger than timeout period " + String(TimeOutPeriod));
      return true;
    } else {
      PRINT_SUDO_ARDUINO("Not reached");
      return false;
    }
}


#include <WiFi.h>

int8_t SudoArduino::connectWifi(const char* ssid, const char* pw, uint16_t TimeOutPeriodMs) { // non blocking since WiFiSTAClass::waitForConnectResult() is blocking
    static unsigned long timeout;
    static bool connectionInitiated = false;
    if (!connectionInitiated) 
    {
        connectionInitiated = true;
        timeout = millis();
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, pw);
        PRINT_SUDO_ARDUINO("Connecting to WiFi ..");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        PRINT_SUDO_ARDUINO("Conn to wifi success");
        PRINT_SUDO_ARDUINO(WiFi.localIP());
        connectionInitiated = false;
        return 1;
    }
    else if (isTimeOut(timeout, TimeOutPeriodMs))
    {
        PRINT_SUDO_ARDUINO("Failed conn to wifi");
        connectionInitiated = false;
        return -1;
    }
    return 0;
    
}