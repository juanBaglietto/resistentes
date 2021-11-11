#include "crossFade.h"
#include "MTimer.h"

int j = 0;

long CrossFade::calculateStep(int prevValue, int endValue)
{
  long step = endValue - prevValue; // What's the overall gap?
  // Serial.print(step);
  // Serial.println();
  if (step)
  {                     // If its non-zero,
    step = 1020 / step; //   divide by 1020
  }
  // Serial.print(step);
  // Serial.println();
  return step;
}

/* The next function is calculateVal. When the loop value, i,
  *  reaches the step size appropriate for one of the
  *  colors, it increases or decreases the value of that color by 1. 
  *  (R, G, and B are each calculated separately.)
  */

int CrossFade::calculateVal(int step, int val, int i)
{

  if ((step) && i % step == 0)
  { // If step is non-zero and its time to change a value,
    if (step > 0)
    { //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0)
    { //   ...or decrement it if step is negative
      val -= 1;
    }
  }

  // Defensive driving: make sure val stays in the range 0-255

  if (val > 255)
  {
    val = 255;
  }
  else if (val < 0)
  {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a 
  *  0-255 range, then loops 1020 times, checking to see if  
  *  the value needs to be updated each time, then writing  
  *  the color values to the correct pins.
  */

void CrossFade::crossFade(Color color)
{

  col_R = color.getRed();
  col_G = color.getGreen();
  col_B = color.getBlue();
  stepR = calculateStep(prevR, col_R);
  stepG = calculateStep(prevG, col_G);
  stepB = calculateStep(prevB, col_B);

  reflector_status = INICIO_CF;

}

int CrossFade::fadeIn()
{

  redVal = calculateVal(stepR, redVal, countFade);
  grnVal = calculateVal(stepG, grnVal, countFade);
  bluVal = calculateVal(stepB, bluVal, countFade);
  countFade++;


  DmxSimple.write(reflectorAddress, redVal);
  DmxSimple.write(reflectorAddress + 1, grnVal);
  DmxSimple.write(reflectorAddress + 2, bluVal);

  if (redVal >= col_R || grnVal >= col_G || bluVal >= col_B)
  {
    Serial.print("Color fade in FIN: ");
    Serial.print(redVal);
    Serial.print(", ");
    Serial.print(grnVal);
    Serial.print(", ");
    Serial.print(bluVal);
    Serial.print("\n");
   // Serial.println("Fin fade IN");
    return -1;
  }
  return 1;
}
int CrossFade::fadeOut()
{
  redVal = calculateVal(-stepR, redVal, countFade);
  grnVal = calculateVal(-stepG, grnVal, countFade);
  bluVal = calculateVal(-stepB, bluVal, countFade);
  countFade++;

  DmxSimple.write(reflectorAddress, redVal);
  DmxSimple.write(reflectorAddress + 1, grnVal);
  DmxSimple.write(reflectorAddress + 2, bluVal);

  if (redVal <= 0 || grnVal <= 0 || bluVal <= 0)
  {
    Serial.println("Fin fade OUT");
    return -1;
  }
  return 1;
}

void CrossFade::setAddress(byte adr)
{
  reflectorAddress = adr;
}
void CrossFade::countFadeUp()
{
  countFade++;
}

void CrossFade::setcountFade(int value)
{
  countFade = value;
}

void CrossFade::setFadeStatus(RefStatus st)
{
  reflector_status = st;
}

RefStatus CrossFade::getFadeStatus()
{
  return reflector_status;
}

void CrossFade::setTFadeIn(int value)
{
  t_fade_in = value;
}

int CrossFade::getTFadeIn()
{
  return t_fade_in;
}

void CrossFade::setTFadeOut(int value)
{
  t_fade_out = value;
}

int CrossFade::getTFadeOut()
{
  return t_fade_out;
}

void CrossFade::setTFade(int value)
{
  t_fade = value;
}

int CrossFade::getTFade()
{
  return t_fade;
}

int CrossFade::getTcountFade()
{
  return countFade;
}

int CrossFade::getFadeDelay_b()
{
  return fade_delay_b;
}