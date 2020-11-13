#include "Domoticz.h"

DOMOTICZ::DOMOTICZ(char* host, int port, char* user, char* password){
    _host = host;
    _port = port;
    _user = user;
    _password = password;
}
 
DOMOTICZ::~DOMOTICZ(){

}

int DOMOTICZ::computeHumStat(float h) {
  int hum_stat;
  if (h > 70) {
    hum_stat = 3;
  } else if (h < 30) {
    hum_stat = 2; 
  } else if (h >= 30 & h <= 45) {
    hum_stat = 0;
  } else if (h > 45 & h <= 70) {
    hum_stat = 1;
  }

  return hum_stat;
}

String DOMOTICZ::buildUrl(float t, float h, int index) {
  int hum_stat = computeHumStat(h);

  String url = _host;
  url += ":";
  url += _port;
  url += "/json.htm?username=";
  url += _user;
  url += "&password=";
  url += _password;
  url += "&type=command&param=udevice&idx=";
  url += String(index);
  url += "&nvalue=0&svalue=";
  url += String(t); 
  url += ";";
  url += String(h); 
  url += ";";
  url += String(hum_stat);
     
  return url;
}

void DOMOTICZ::notify(float t, float h, int index){
  String url = buildUrl(t, h, index);

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();

  Serial.print("Requesting URL: ");
  Serial.println(url);
  _http.begin(*client, url);
  int httpCode = _http.GET();
    if (httpCode) {
      if (httpCode == 200) {
        String payload = _http.getString();
        Serial.println("Domoticz response "); 
        Serial.println(payload);
      } else {
        Serial.println(httpCode);        
      }
    }
  Serial.println("closing connection");
  _http.end();
}
