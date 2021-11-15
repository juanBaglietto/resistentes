
#include <Arduino_FreeRTOS.h>
#include "colors.h"
#include "director.h"

Reflector reflector1;
Reflector reflector2;
Reflector reflector3;
Reflector reflector4;
ReflectorHandler reflectors;
Director resistentes;

extern void AnalizarTimer(void);
void initReflectors();
void crossFade(int address_base, int color[3]);
Reflector *parserReflector(String msg);


void ISR_timer1()
{
  AnalizarTimer();
}

void setup()
{

  initReflectors();
  pinMode(LED_BUILTIN, OUTPUT);
  Timer1.initialize(10000); // timer 1 interrumpe cada 100ms
  Timer1.attachInterrupt(ISR_timer1);
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  Serial.println("Resistentes \n");
  resistentes.init(&reflectors);
  resistentes.setScene(SCENE_1);
}

void initReflectors()
{
  reflector1.initReflector(ADDRESS_BASE_REFL_1);

  Color coloinit;
  coloinit.changeColor(238, 102, 8);
  reflector1.setColor(coloinit);
  reflector1.setTimeCrossFade(2,5,2);
  reflectors.addReflector(&reflector1);

  //coloinit.changeColor(30, 20, 80);
  reflector2.initReflector(ADDRESS_BASE_REFL_2);
  reflector2.setColor(coloinit);
  reflector2.setTimeCrossFade(2,5,2);
  reflectors.addReflector(&reflector2);

  reflector3.initReflector(ADDRESS_BASE_REFL_3);
  reflector3.setColor(coloinit);
  reflector3.setTimeCrossFade(2,5,2);
  reflectors.addReflector(&reflector3);

  reflector4.initReflector(ADDRESS_BASE_REFL_4);
  reflector4.setColor(coloinit);
  reflector4.setTimeCrossFade(2,5,2);
  reflectors.addReflector(&reflector4);
}

void loop()
{
  TmrEvent();
  resistentes.updateScenes();
  reflectors.UpdateAllReflectors();
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

//void TaskSerial()
// {
//   Reflector *reflectorSelec;

//     if (Serial.available())
//     {
//       String msg_read = Serial.readStringUntil(' ');
//       Serial.print("llego: ");
//       Serial.print(msg_read);
//       Serial.print("\n");

//       if (msg_read == "manual")
//       {
//         // _action = MANUAL;
//         String msg_reflector = Serial.readStringUntil(' ');
//         String msg_status = Serial.readStringUntil('\n');
//         Serial.println("Camando Manual");
//         reflectorSelec = parserReflector(msg_reflector);

//         if (msg_status == "on")
//         {
//           Serial.println("on");

//           reflectorSelec->setStatus(true);
//         }
//         else
//         {
//           Serial.println("off");
//           reflectorSelec->setStatus(false);
//         }
//       }
//       else if (msg_read == "color")
//       {
//         // _action = MANUAL;
//         String msg_reflector = Serial.readStringUntil(' ');
//         String msg_red = Serial.readStringUntil(' ');
//         String msg_green = Serial.readStringUntil(' ');
//         String msg_blue = Serial.readStringUntil('\n');
//         Serial.println("Camando Color");
//         Color colorAux;
//         colorAux.changeColor(msg_red.toInt(), msg_green.toInt(), msg_blue.toInt());
//         if (msg_reflector == "all")
//         {
//           reflector1.setColor(colorAux);
//           reflector2.setColor(colorAux);
//         }
//         else
//         {
//           reflectorSelec = parserReflector(msg_reflector);
//           reflectorSelec->setColor(colorAux);
//         }
//       }
//       else
//       {
//         Serial.readString();
//       }
//     }

// }