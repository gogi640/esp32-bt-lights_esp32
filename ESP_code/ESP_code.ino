#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial *BT;
char *json = new char[100];

void setup() {
  // put your setup code here, to run once:
  BT = new BluetoothSerial();
  BT->begin("BMW");
  StaticJsonDocument<100> doc;
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  int i=0;
  while(BT->available())
  {
    json[i] =BT->read();
    i++;
    delayMicroseconds(100);
  }
  if(i!=0)
  {
    Serial.println(i);
    BT->println("DA");
    for(int j=0;j<i;j++)
    {
      if(json[j] < 10) Serial.print("0");
      Serial.print(json[j],1);
    }
    Serial.println();
    Serial.println("Outputed!");
   // doThing();
  }
}