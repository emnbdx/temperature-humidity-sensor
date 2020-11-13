#ifndef DOMOTICZ_H
#define DOMOTICZ_H
 
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
 
class DOMOTICZ {
public:
        DOMOTICZ(char* host, int port, char* user, char* password);
        ~DOMOTICZ();
        void notify(float t, float h, int index);
private:
        HTTPClient _http;
        char* _host;
        int _port;
        char* _user;
        char* _password;
        int computeHumStat(float h);
        String buildUrl(float t, float h, int index);
};
 
#endif
