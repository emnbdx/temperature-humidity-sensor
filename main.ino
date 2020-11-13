#include <ESP8266WiFi.h>
#include "DHT.h"
#include "Domoticz.h"

#define DHTTYPE DHT22

const char* ssid = "MyWifi"; // Add wifi SSID here
const char* password = "123456"; // Add wifi password here
               
DHT dht1(D1, DHTTYPE);
DHT dht2(D2, DHTTYPE);

DOMOTICZ d("https://domoticz.local", 8080, "user", "password"); // Add domoticz configuration here
 
void setup() {
  Serial.begin(115200);
  delay(100);
  
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);

  dht1.begin();
  dht2.begin();
}

void loop() {
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  
  float t1 = dht1.readTemperature();
  float h1 = dht1.readHumidity();
  d.notify(t1, h1, 0); // Add domoticz devices idx here
  float t2 = dht2.readTemperature();
  float h2 = dht2.readHumidity();
  d.notify(t2, h2, 0); // Add domoticz devices idx here

  WiFi.disconnect();
  Serial.println("WiFi disconnected");

  delay (10 * 1000);
}
