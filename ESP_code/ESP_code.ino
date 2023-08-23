#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial *BT;

void setup() {
  // put your setup code here, to run once:
  BT = new BluetoothSerial();
  BT->begin("BMW");
  StaticJsonDocument<100> doc;
  char *json = new char[100];
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(BT->available())
  {
    Serial.print(BT->read());  
  }
}
