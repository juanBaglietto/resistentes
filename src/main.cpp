
#include <Arduino_FreeRTOS.h>
#include "colors.h"
#include "reflectorHandler.h"



enum todasLasEscenas
{
  ESCENA_1,
  ESCENA_2,
  ESCENA_3,
} escenaActual;



enum Escena1
{
  E1_INICIO,
  E1_PASO_1,
  E1_PASO_2,
  E1_PASO_3,
  E1_PASO_4,
  E1_PASO_5,
  E1_PASO_6,
  E1_FIN,
} statusE1;



enum Escena2
{
  E2_INICIO,
  E2_PASO_1,
  E2_PASO_2,
  E2_PASO_3,
  E2_PASO_4,
  E2_PASO_5,
  E2_PASO_6,
  E2_FIN,
} statusE2;

Reflector reflector1;
Reflector reflector2;
Reflector reflector3;
Reflector reflector4;
Reflector *reflectorSelec;
ReflectorHandler reflectors;

extern void AnalizarTimer(void);
void initRelectores();
void crossFade(int address_base, int color[3]);
Reflector *parserReflector(String msg);
void analizarEscenas();
void analizarEscena_1();
void analizarEscena_2();
void analizarEscena_3();


void ISR_timer1()
{
  AnalizarTimer();
}

void setup()
{

  initRelectores();
  pinMode(LED_BUILTIN, OUTPUT);
  Timer1.initialize(10000); // timer 1 interrumpe cada 100ms
  Timer1.attachInterrupt(ISR_timer1);
  Serial.begin(9600);
  while (!Serial)
  {
    ;
  }
  Serial.println("Resistentes \n");
  escenaActual=ESCENA_1;
}

void initRelectores()
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
  analizarEscenas();
  reflectors.UpdateAllReflectors();
}

void analizarEscenas()
{
  switch (escenaActual)
  {
  case ESCENA_1:
    analizarEscena_1();
    break;
  case ESCENA_2:
    analizarEscena_2();
    break;
  case ESCENA_3:
    analizarEscena_3();
    break;

  default:
    break;
  }
}

void analizarEscena_1()
{
  switch (statusE1)
  {
  case E1_INICIO:
    reflectors.getReflector(0)->setReflectorStatus(INICIO_CF);
    statusE1 = E1_PASO_1;
    break;
  case E1_PASO_1:
    if (reflectors.getReflector(0)->getReflectorStatus() == FADE_OUT && reflectors.getReflector(0)->getPercentFadeOut() >= 90)
    {
      reflectors.getReflector(1)->setReflectorStatus(INICIO_CF);
      statusE1 = E1_PASO_2;
    }
    break;
  case E1_PASO_2:
    if (reflectors.getReflector(1)->getReflectorStatus() == FADE_OUT && reflectors.getReflector(1)->getPercentFadeOut() >= 50)
    {
      statusE1 = E1_INICIO;
    }
    break;
  case E1_PASO_3:
    break;
  case E1_PASO_4:
    break;
  case E1_PASO_5:
    break;
  case E1_PASO_6:
    break;
  case E1_FIN:
    break;

  default:
    break;
  }
  
}

void analizarEscena_2()
{
  switch (statusE2)
  {
  case E2_INICIO:
    reflectors.getReflector(0)->setReflectorStatus(INICIO_CF);
    reflectors.getReflector(1)->setReflectorStatus(INICIO_CF);
    statusE2 = E2_PASO_1;
    break;
  case E2_PASO_1:
    if (reflectors.getReflector(1)->getReflectorStatus() == FADE_OUT && reflectors.getReflector(1)->getPercentFadeOut() >= 90)
    {
      reflectors.getReflector(2)->setReflectorStatus(INICIO_CF);
      reflectors.getReflector(3)->setReflectorStatus(INICIO_CF);
      statusE2 = E2_PASO_2;
    }
    break;
  case E2_PASO_2:
    if (reflectors.getReflector(3)->getReflectorStatus() == FADE_OUT && reflectors.getReflector(3)->getPercentFadeOut() >= 50)
    {
      statusE2 = E2_INICIO;
    }
    break;
  case E2_PASO_3:
    break;
  case E2_PASO_4:
    break;
  case E2_PASO_5:
    break;
  case E2_PASO_6:
    break;
  case E2_FIN:
    break;

  default:
    break;
  }
  
}
void analizarEscena_3()
{}


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