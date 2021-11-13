
#include <Arduino_FreeRTOS.h>
#include "colors.h"
#include "MTimer.h"
#include "reflectorHandler.h"

#define STEP_FADE_IN_ms 1
#define STEP_FADE_OUT_ms 1
#define DELAY_FULL 1

enum Escena1
{
  INICIO_E1,
  PASO_1,
  PASO_2,
  PASO_3,
  PASO_4,
  PASO_5,
  PASO_6,
  FIN_E1,
} statusE1;

extern void AnalizarTimer(void);

RefStatus status_actual;

byte _address_manual = ADDRESS_BASE_REFL_1;
int _color[3] = {75, 10, 0};
int fadeInStatus = 0;
int fadeOutStatus = 0;


Reflector reflector1;
Reflector reflector2;
Reflector *reflectorSelec;
ReflectorHandler reflectores;

void initRelectores();
void crossFade(int address_base, int color[3]);
Reflector *parserReflector(String msg);
void analizarFade();
void analizarEscenas();

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
}

void initRelectores()
{
  reflector1.initReflector(ADDRESS_BASE_REFL_1);

  Color coloinit;
  coloinit.changeColor(238,102, 8);
  reflector1.setColor(coloinit);
  reflector1._crossFade.setTFade(5);
  reflectores.addReflector(&reflector1);


  //coloinit.changeColor(30, 20, 80);
  reflector2.initReflector(ADDRESS_BASE_REFL_2);
  reflector2.setColor(coloinit);
  reflector2._crossFade.setTFade(5);
  reflectores.addReflector(&reflector2);

}



void loop()
{
  TmrEvent();
  analizarFade();
  analizarEscenas();
}

void analizarEscenas()
{
  switch (statusE1)
  {
  case INICIO_E1:
    reflectores.getReflector(0)->initCrossFade();
    statusE1 = PASO_1;
    break;
  case PASO_1:
    if (reflectores.getReflector(0)->_crossFade.getFadeStatus() == FADE_OUT && reflectores.getReflector(0)->_crossFade.getPorFadeOut()>=90)
    {
      reflectores.getReflector(1)->initCrossFade();
      statusE1 = PASO_2;
    }
    break;
  case PASO_2:
    if (reflectores.getReflector(1)->_crossFade.getFadeStatus() == FADE_OUT && reflectores.getReflector(1)->_crossFade.getPorFadeOut()>=50)
    {
      statusE1 = INICIO_E1;
    }
    break;
  case PASO_3:
    break;
  case PASO_4:
    break;
  case PASO_5:
    break;
  case PASO_6:
    break;
  case FIN_E1:
    break;

  default:
    break;
  }
}
void analizarFade()
{

  for (byte i = 0; i < reflectores.getCantReflectoresEnUso(); i++)
  {

    status_actual = reflectores.getReflector(i)->_crossFade.getFadeStatus();

    switch (status_actual)
    {
    case ESPERA_CF:

      break;
    case INICIO_CF:
      //TmrStart(EVENTO0, reflectorSelec->_crossFade.getTFadeIn());
      reflectores.getReflector(i)->_crossFade.setFadeStatus(FADE_IN);
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case FADE_IN:
      fadeInStatus = reflectores.getReflector(i)->_crossFade.fadeIn();
      delay(STEP_FADE_IN_ms);
      if (fadeInStatus == -1)
      {
        digitalWrite(LED_BUILTIN, LOW);
        reflectores.getReflector(i)->_crossFade.setFadeStatus(FULL);
        reflectores.getReflector(i)->_crossFade.setcountFade(0);
        reflectorSelec = reflectores.getReflector(i);
        TmrStart(EVENTO1, reflectorSelec->_crossFade.getTFade());
      }

      break;
    case FULL:
      delay(DELAY_FULL);
      break;

    case FADE_OUT:
      fadeOutStatus = reflectores.getReflector(i)->_crossFade.fadeOut();
      delay(STEP_FADE_OUT_ms);
      if (fadeOutStatus == -1)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        reflectores.getReflector(i)->_crossFade.setFadeStatus(FIN_CF);
        reflectores.getReflector(i)->_crossFade.setcountFade(0);
      }
      break;
    case FIN_CF:
      delay(DELAY_FULL);
      break;

    default:
      break;
    }
  }
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