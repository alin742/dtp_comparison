#include "Arduino.h"
#include "WiFi.h"
#include "time.h"

/*
* WIFICredentials.h: a header file that defines all
*   the personal WIFI settings. The file contains the
*   following defientions:
*   
*   #define SSID "[YOUR WIFI SSID]"
*   #define PASS "[YOUR WIFI PASSWORD]"
*   #define NTP_SERVER1 "[YOUR PREFFERED NTP SERVER]"
*   #define NTP_SERVER2 "[A BACKUP NTP SERVER USUALLY pool.ntp.org]"
*   #define GMT_OFFSET 3600 // the difference from your timezone to GMT in seconds
*   #define DAYLIGHT_OFFSET 3600 // daylight saving offset in seconds
*/
#include "../../WIFICredentials.h"
#define BAUDRATE 921600

int64_t
getTime()
{
  struct timeval tv_now;
  gettimeofday(&tv_now, NULL);
  return (int64_t)tv_now.tv_sec * 1000000L + (int64_t)tv_now.tv_usec;
}

void
WiFiConnectingAnimation()
{
  for (int i = 0; i < 50; i++)
    Serial.print(".");
  Serial.println("");
  Serial.println("INFO: Connecting to WiFi");
}

void
SyncNTPServer()
{
  // Synchronize Time with NTP_SERVER1 and NTP_SERVER2
  Serial.print("INFO: Syncronizing Time with NTP Server: ");
  Serial.print(NTP_SERVER1);
  Serial.print(", ");
  Serial.println(NTP_SERVER2);
  configTime(GMT_OFFSET, DAYLIGHT_OFFSET, NTP_SERVER1, NTP_SERVER2);
  delay(2000);
}

void
setup()
{
  Serial.begin(BAUDRATE);
  WiFi.begin(SSID, PASS);
  Serial.println("INFO: Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    WiFiConnectingAnimation();
  }
  SyncNTPServer();
  // disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void
loop()
{
  Serial.print("Test (");
  Serial.print(getTime());
  Serial.println(")");
  // delay(5);
}
