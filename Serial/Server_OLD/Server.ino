#include <WiFi.h>
#include <sys/time.h>
#include "../../WIFICredentials.h"
#define BUFF_SZ 1
#define BAUDRATE 2000000

const char* ntpServer = "pool.ntp.org";

uint64_t getEpoch_us() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  uint64_t time_us = (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec;
  return time_us;
}

void setup() {
  Serial.begin(BAUDRATE);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while(1) {
      delay(1000);
    }
  }
  configTime(0, 0, ntpServer);
  delay(1000);
}

void loop() {
  String buff = "";
  for (int i=0; i<BUFF_SZ; i++)
    buff+= String(getEpoch_us())+" -> anyone here?\r\n";
  Serial.write(buff.c_str());
} 