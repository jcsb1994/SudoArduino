#include "SudoArduino.h"


#if DEBUG_SUDOARDUINO
#define PRINT(msg) Serial.println(msg)
#else
#define PRINT(msg) 
#endif

#if DEBUG_SUDOARDUINO==2
#define PRINT_VERBOSE(msg) Serial.println(msg)
#else
#define PRINT_VERBOSE(msg) 
#endif


bool SudoArduino::isTimeOut(unsigned long &startTime, unsigned long TimeOutPeriod) {
    unsigned long gap;
    PRINT_VERBOSE("Start time: " + String(startTime));
    if (millis() < startTime) {   // in case of overflow
      PRINT("Millis Overflow");
      gap = (MAX_ULONG_VALUE - startTime) + millis() + 1;
    } else {
      PRINT_VERBOSE("Calculating time between now and timer start: " + String(millis()) + " " + String(startTime));
      gap = millis() - startTime;
    }  
    if (gap >= TimeOutPeriod) {
      PRINT_VERBOSE(String(gap) + " is bigger than timeout period " + String(TimeOutPeriod));
      return true;
    } else {
      PRINT_VERBOSE("Not reached");
      return false;
    }
}

#ifdef ESP32

#include <WiFi.h>
#include <time.h>

int8_t SudoESP32::connectWifi(const char* ssid, const char* pw, uint16_t TimeOutPeriodMs) { // non blocking since WiFiSTAClass::waitForConnectResult() is blocking
    static unsigned long timeout;
    static bool connectionInitiated = false;
    if (!connectionInitiated) 
    {
        connectionInitiated = true;
        timeout = millis();
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, pw);
        PRINT("Connecting to WiFi ..");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        PRINT("Conn to wifi success");
        PRINT(WiFi.localIP());
        connectionInitiated = false;
        return 1;
    }
    else if (SudoArduino::isTimeOut(timeout, TimeOutPeriodMs))
    {
        PRINT("Failed conn to wifi");
        connectionInitiated = false;
        return -1;
    }
    return 0;
}

uint32_t SudoESP32::getUnixTime()
{
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        PRINT("Failed to obtain time from ESP32");
        return 0;
    }
    time(&now);
    return now;
}


#endif