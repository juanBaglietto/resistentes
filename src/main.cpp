
#include <Arduino_FreeRTOS.h>
#include "crossFade.h"
#include "reflector.h"
#include "colors.h"


int _address = ADDRESS_BASE_REFL_1;
int _color[3] = {0, 0, 100};


void crossFade(int address_base, int color[3]);

void TaskSerial(void *pvParameters);
void TaskCrossFade(void *pvParameters);

void setup()
{

  xTaskCreate(TaskSerial, "Serial", 128, NULL, 2, NULL);
  xTaskCreate(TaskCrossFade, "CrossFade", 128, NULL, 2, NULL);
}
void loop() {
  
}


void TaskSerial(void *pvParameters) 
{

  (void)pvParameters;
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Resistentes \n");
  for (;;) 
  {
    while (Serial.available() > 0)
    {
      String command = Serial.readStringUntil(' ');
      String reflector = Serial.readStringUntil(' ');
      String color = Serial.readStringUntil('\n');
      if (command == "manual")
      {
        Serial.print("Camando Manual");
        Serial.print('\n');
        Serial.print(reflector);
        Serial.print('\n');
        Serial.print(color);
        Serial.print('\n');

        if (reflector == "r1")
        {
          Serial.print("reflector 1");
          _address = ADDRESS_BASE_REFL_1;
        }
        else if (reflector == "r2")
        {
          Serial.print("reflector  2");
          _address = ADDRESS_BASE_REFL_2;
        }

        if (color == "red")
        {
          Serial.print("Color Rojo");
          _color[0] = red[0];
          _color[1] = red[1];
          _color[2] = red[2];
        }
        else if (color == "green")
        {
          Serial.print("Color verde");
          _color[0] = green[0];
          _color[1] = green[1];
          _color[2] = green[2];
        }
      }
    }
  }
}


void TaskCrossFade(void *pvParameters)
{
  for (;;) 
  {
    crossFade(_address, _color);
  }
}