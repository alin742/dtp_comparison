#include "Arduino.h"

#define BAUDRATE 921600

int count = 0;

void
setup()
{
  Serial.begin(BAUDRATE);
}

void
loop()
{
  Serial.print("Test ");
  Serial.println(count++);
  delay(5);
}
