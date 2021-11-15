#include "reflector.h"
#include <DmxSimple.h>

void Reflector::initReflector(byte address)
{
    _address = address;
    crossFade.setAddress(_address);
}

void Reflector::setColor(Color color)
{

    _color.changeColor(color.getRed(), color.getGreen(), color.getBlue());
    // DmxSimple.write(_address, color.getRed());
    // DmxSimple.write(_address + 1, color.getGreen());
    // DmxSimple.write(_address + 2, color.getBlue());
}

void Reflector::manualOnOff(bool on)
{

    reflectorOn = on;
    if (reflectorOn)
    {
        setColor(_color);
    }
    else
    {

        DmxSimple.write(_address, 0);
        DmxSimple.write(_address + 1, 0);
        DmxSimple.write(_address + 2, 0);
    }
}

bool Reflector::isReflectorOn()
{
    return reflectorOn;
}

int Reflector::getPercentFadeOut()
{
    return crossFade.getPercentFadeOut();
}
void Reflector::setTimeCrossFade(int t_in,int t_full,int t_out)
{
    crossFade.setTFadeIn(t_in);
    crossFade.setTFadeFull(t_full);
    crossFade.setTFadeOut(t_out);
}
void Reflector::setReflectorStatus(ReflectorStatus refStatus)
{
    reflectorStatus=refStatus;
}

ReflectorStatus Reflector::getReflectorStatus()
{
 return reflectorStatus;
}

void Reflector::updateStatus()
{
    int fadeInStatus=0;
    int fadeOutStatus=0;
    switch (reflectorStatus)
    {
    case ESPERA_CF:

      break;
    case INICIO_CF:
      //TmrStart(EVENTO0, reflectorSelec->_crossFade.getTFadeIn());
      crossFade.crossFade(_color);
      reflectorStatus=FADE_IN;
      break;
    case FADE_IN:
      fadeInStatus = crossFade.fadeIn();
      delay(STEP_FADE_IN_ms);
      if (fadeInStatus == -1)
      {
        reflectorStatus=FULL;
        crossFade.setcountFade(0);
        TmrStart(EVENTO1, crossFade.getTFadeFull());
      }

      break;
    case FULL:
      delay(DELAY_FULL);
      break;

    case FADE_OUT:
      fadeOutStatus = crossFade.fadeOut();
      delay(STEP_FADE_OUT_ms);
      if (fadeOutStatus == -1)
      {
        reflectorStatus=FIN_CF;
        crossFade.setcountFade(0);
      }
      break;
    case FIN_CF:
      delay(DELAY_FULL);
      break;

    default:
      break;
    }
  
}