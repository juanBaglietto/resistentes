
#include <Arduino_FreeRTOS.h>
#include "reflector.h"
#include "colors.h"
#include "MTimer.h"
#define MAX_REFLECTOR 6
#define STEP_FADE_IN_ms 40
#define STEP_FADE_OUT_ms 40
#define DELAY_FULL 1

extern void AnalizarTimer(void);

RefStatus status_actual;

byte _address_manual = ADDRESS_BASE_REFL_1;
int _color[3] = {75, 10, 0};
int fadeInStatus = 0;
int fadeOutStatus = 0;
byte reflectoresEnUso = 0;

Reflector reflector1;
Reflector reflector2;
Reflector *reflectorSelec;
Reflector *reflectores[MAX_REFLECTOR];

void initRelectores();
void crossFade(int address_base, int color[3]);
Reflector *parserReflector(String msg);
void analizarFade();


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
  reflectores[0]->initCrossFade();
}

void initRelectores()
{
  reflector1.initReflector(ADDRESS_BASE_REFL_1);

  Color coloinit;
  coloinit.changeColor(30, 20, 80);
  reflector1.setColor(coloinit);
  reflector1._crossFade.setTFade(20);
  reflectores[0] = &reflector1;

  coloinit.changeColor(30, 20, 80);
  reflector2.initReflector(ADDRESS_BASE_REFL_2);
  reflector2.setColor(coloinit);
  reflectores[1] = &reflector2;
  reflectoresEnUso = 2;
}

void loop()
{
  TmrEvent();
  analizarFade();
}

int reflector_status = 0;

void analizarFade()
{

  for (byte i = 0; i < reflectoresEnUso; i++)
  {

    status_actual = reflectores[i]->_crossFade.getFadeStatus();

    switch (status_actual)
    {
    case ESPERA:

      break;
    case INICIO:
      //TmrStart(EVENTO0, reflectorSelec->_crossFade.getTFadeIn());
      reflectores[i]->_crossFade.setFadeStatus(FADE_IN);
      digitalWrite(LED_BUILTIN, HIGH);
      break;
    case FADE_IN:
      fadeInStatus = reflectores[i]->_crossFade.fadeIn();
      delay(STEP_FADE_IN_ms);
      if (fadeInStatus == -1)
      {
        digitalWrite(LED_BUILTIN, LOW);
        reflectores[i]->_crossFade.setFadeStatus(FULL);
        reflectores[i]->_crossFade.setcountFade(0);
        reflectorSelec=reflectores[i];
        TmrStart(EVENTO1, reflectorSelec->_crossFade.getTFade());
      }

      break;
    case FULL:
      delay(DELAY_FULL);
      break;

    case FADE_OUT:
      fadeOutStatus = reflectores[i]->_crossFade.fadeOut();
      delay(STEP_FADE_OUT_ms);
      if (fadeOutStatus == -1)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        reflectores[i]->_crossFade.setFadeStatus(ESPERA);
        reflectores[i]->_crossFade.setcountFade(0);
      }
      break;
    default:
      break;
    }
  }

  // if (reflector1._crossFade.getFadeStatus() == 1)
  // {
  //   fadeInStatus=reflector1._crossFade.fadeIn();
  //   if(fadeInStatus==-1)
  //   {
  //     reflector1._crossFade.setFadeStatus(3);
  //     reflector1._crossFade.setcountFade(0);
  //     TmrStart(EVENTO3, reflector1._crossFade.getTFade());
  //   }
  //   else
  //   {
  //     reflector1._crossFade.countFadeUp();
  //   }

  //   delay(reflector1._crossFade.getFadeDelay_b());
  // }
  // else if (reflector1._crossFade.getFadeStatus() == 2)
  // {
  //   reflector1._crossFade.fadeOut();
  //   reflector1._crossFade.countFadeUp();
  //   delay(reflector1._crossFade.getFadeDelay_b());
  // }
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