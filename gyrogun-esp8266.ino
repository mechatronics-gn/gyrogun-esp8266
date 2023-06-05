#include<ESP8266WiFi.h>
#include "secrets.h"

WiFiClient client;
IPAddress host HOST_IP;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(MECHANET_SSID, MECHANET_PW);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

int cnt = 0;
uint8_t buffer[16] = {};

void loop() {  
  if(!client.connected()) {
    Serial.write(0);
    cnt = 0;
    client.connect(host, HOST_PORT);
    delay(1000);
    while (Serial.available()) {
      Serial.read();
      delayMicroseconds(250);
    }
  } else {
    Serial.write(1);
  }
  
  if(Serial.available()) {
    if (cnt < 16) buffer[cnt++] = Serial.read();
    if (cnt == 16) {
      client.write(buffer, 16);
      cnt = 0;
    }
  }
  delayMicroseconds(250);
}
