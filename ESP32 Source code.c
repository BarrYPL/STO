#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

#define STO_PIN 19
#define HIGH_PIN 18

int x;

void setup() { 
  Serial.begin(115200);
  SerialBT.begin("STO Button");
  pinMode(STO_PIN, INPUT);
  pinMode(HIGH_PIN, OUTPUT);
  digitalWrite(HIGH_PIN, HIGH);
}

void loop() {
  x = digitalRead(STO_PIN);
  delay(50);
  if (x == 0) 
  {
    SerialBT.println(1);
    while(1)
    {
      x = digitalRead(STO_PIN);
      if (x == 1) 
      {
        SerialBT.println(2);
        break;
      }
    }
  }
  delay(50);
}
