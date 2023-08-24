#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial *BT;
char *json = new char[100];
StaticJsonDocument<100> doc;

int* left = new int(4);
int* right = new int(4);
int* lightState;

void setup() {
  // put your setup code here, to run once:
  BT = new BluetoothSerial();
  BT->begin("BMW");
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
    DeserializationError error = deserializeJson(doc, json);

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      BT->println("NE");
    }
    else
    {
      BT->println("DA");
      *lightState = doc["lightState"];
      for(int k=0;k<4;k++)
      {
        left[k] = doc["left"][k];
        right[k] = doc["right"][k];
      }
      dumpAll();
    }
    /*
    Serial.println(i);
    BT->println("DA");
    for(int j=0;j<i;j++)
    {
      if(json[j] < 10) Serial.print("0");
      Serial.print(json[j],1);
    }
    Serial.println();
    Serial.println("Outputed!");
   // doThing();*/
  }
}

void dumpAll()
{
  Serial.print("lightState: ");
  Serial.println(*lightState);
  Serial.print("LR: ");
  Serial.println(left[0]);
  Serial.print("LG: ");
  Serial.println(left[1]);
  Serial.print("LB: ");
  Serial.println(left[2]);
  Serial.print("LW: ");
  Serial.println(left[3]);
  Serial.print("RR: ");
  Serial.println(right[0]);
  Serial.print("RG: ");
  Serial.println(right[1]);
  Serial.print("RB: ");
  Serial.println(right[2]);
  Serial.print("RW: ");
  Serial.println(right[3]);
}