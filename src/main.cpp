
#include <Arduino_FreeRTOS.h>
#include "reflector.h"
#include "colors.h"

static enum Action { MANUAL,
                     ESCENA_1,
                     ESCENA_2,
                     ESCENA_3,
                     ESCENA_4,
} _action;

int _address_manual = ADDRESS_BASE_REFL_1;
int _color[3] = {75, 10, 0};

Reflector reflector1;
Reflector reflector2;
Reflector reflectorSelec;

void initRelectores();
void crossFade(int address_base, int color[3]);
Reflector *parserReflector(String msg);
//Color parserColor(String msg_red, String msg_green, String msg_blue);

void TaskSerial(void *pvParameters);
void TaskCrossFade(void *pvParameters);

void setup()
{
  initRelectores();
  xTaskCreate(TaskSerial, "Serial", 128, NULL, 2, NULL);
  xTaskCreate(TaskCrossFade, "CrossFade", 128, NULL, 2, NULL);
}
void loop()
{
}

void TaskSerial(void *pvParameters)
{
  (void)pvParameters;
  Reflector *reflectorSelec;
  Serial.begin(9600);
  while (!Serial)
  {
    ; // wait for serial port to connect. Needed for native USB
  }
  Serial.println("Resistentes \n");
  for (;;)
  {
    if (Serial.available())
    {
      String msg_read = Serial.readStringUntil(' ');
      Serial.print("llego: ");
      Serial.print(msg_read);
      Serial.print("\n");

      if (msg_read == "manual")
      {
        // _action = MANUAL;
        String msg_reflector = Serial.readStringUntil(' ');
        String msg_status = Serial.readStringUntil('\n');
        Serial.println("Camando Manual");
        reflectorSelec = parserReflector(msg_reflector);

        if (msg_status == "on")
        {
          Serial.println("on");
          reflectorSelec->setStatus(true);
        }
        else
        {
          Serial.println("off");
          reflectorSelec->setStatus(false);
        }
      }
      else if (msg_read == "color")
      {
        // _action = MANUAL;
        String msg_reflector = Serial.readStringUntil(' ');
        String msg_red = Serial.readStringUntil(' ');
        String msg_green = Serial.readStringUntil(' ');
        String msg_blue = Serial.readStringUntil('\n');
        Serial.println("Camando Color");
        Color colorAux;
        colorAux.changeColor(msg_red.toInt(), msg_green.toInt(), msg_blue.toInt());
        if (msg_reflector == "all")
        {
          reflector1.setColor(colorAux);
          reflector2.setColor(colorAux);
        }
        else
        {
          reflectorSelec = parserReflector(msg_reflector);
          reflectorSelec->setColor(colorAux);
        }
      }
      else
      {
        Serial.readString();
      }
    }
  }
}

void TaskCrossFade(void *pvParameters)
{
  for (;;)
  {
    switch (_action)
    {
    case MANUAL:
      break;
    case ESCENA_1:

      break;

    default:
      break;
    }
    reflector1.initCrossFade();
    reflector2.initCrossFade();
  }
}

void initRelectores()
{
  reflector1.initReflector(ADDRESS_BASE_REFL_1);

  Color coloinit;
  coloinit.changeColor(0, 20, 45);
  reflector1.setColor(coloinit);
  coloinit.changeColor(0, 20, 45);
  reflector2.initReflector(ADDRESS_BASE_REFL_2);
  reflector2.setColor(coloinit);
}

Reflector *parserReflector(String msg)
{
  Reflector *null_r;

  if (msg == "r1")
  {
    Serial.println("reflector 1");
    return &reflector1;
  }
  else if (msg == "r2")
  {
    Serial.println("reflector  2");
    return &reflector2;
  }
  return null_r;
}
