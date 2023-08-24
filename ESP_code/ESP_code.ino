#include "BluetoothSerial.h"
#include <ArduinoJson.h>

BluetoothSerial *BT;
char *json = new char[100];
StaticJsonDocument<100> doc;

uint8_t* left = new uint8_t(4);
uint8_t* right = new uint8_t(4);
uint8_t* lightState;
bool* policeMode = 0;
bool* inputExist = 0;
uint8_t* inputSize = 0;

void setup() {
  // put your setup code here, to run once:
  BT = new BluetoothSerial();
  BT->begin("BMW");
  Serial.begin(115200);
}

void loop() {
  if(BT->available()) 
  {
    *inputSize = BtReceive();
    *inputExist = 1;
    processInput();
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

bool processInput()
{
  if(*inputExist)
  {
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      BT->println("NE");
      return 0;
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
      memset(json, 0, 100 * sizeof(char));
      dumpAll();
    }
    *inputExist = 0;
  }

  switch(*lightState)
  {
    case 1:
      *policeMode = 1;
      break;
    case 2:
      //...
      break;
    default:
      //...
      break;
  }
  return 1;
}

int BtReceive()
{
  int i=0;
  while(BT->available())
  {
    json[i] =BT->read();
    i++;
    delayMicroseconds(100);
  }
  return i;
}