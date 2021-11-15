#include "crossFade.h"
#include "MTimer.h"
#define STEP_DIV 2500

int j = 0;

long CrossFade::calculateStep(int prevValue, int endValue)
{
  long step = endValue - prevValue; // What's the overall gap?
  // Serial.print(step);
  // Serial.println();
  if (step)
  {                     // If its non-zero,
    step = STEP_DIV / step; //   divide by 1020
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
    // Serial.print("steps: ");
    // Serial.print(stepR );
    // Serial.print(", ");
    // Serial.print(stepG );
    // Serial.print(", ");
    // Serial.print(stepB );
    // Serial.print("\n");

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

  if (countFade>=STEP_DIV)
  {
    // Serial.print("Color fade in FIN: ");
    // Serial.print(redVal);
    // Serial.print(", ");
    // Serial.print(grnVal);
    // Serial.print(", ");
    // Serial.print(bluVal);
    // Serial.print("\n");
    // Serial.print("Contador: ");
    // Serial.print(countFade);
    // Serial.print("\n");
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
  percentFadeOut=(countFade*100)/STEP_DIV;
  DmxSimple.write(reflectorAddress, redVal);
  DmxSimple.write(reflectorAddress + 1, grnVal);
  DmxSimple.write(reflectorAddress + 2, bluVal);

  if (countFade>=STEP_DIV)
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
void CrossFade::setcountFade(int value)
{
  countFade = value;
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

void CrossFade::setTFadeFull(int value)
{
  t_fade_full = value;
}

int CrossFade::getTFadeFull()
{
  return t_fade_full;
}

int CrossFade::getTcountFade()
{
  return countFade;
}

int CrossFade::getPercentFadeOut()
{
  return percentFadeOut;
}