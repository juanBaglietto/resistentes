#include "crossFade.h"

int j = 0;   



void CrossFade::setAddress(int adr)
{
  reflectorAddress=adr;
}


int CrossFade::calculateStep(int prevValue, int endValue)
{
  int step = endValue - prevValue; // What's the overall gap?
  if (step)
  {                     // If its non-zero,
    step = 1020 / step; //   divide by 1020
  }
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

void CrossFade::crossFade( Color color)
{
  // Convert to 0-255

  int R = (color.getRed() * 255) / 100;
  int G = (color.getGreen() * 255) / 100;
  int B = (color.getBlue() * 255) / 100;

  int stepR = calculateStep(prevR, R);
  int stepG = calculateStep(prevG, G);
  int stepB = calculateStep(prevB, B);

  for (int i = 0; i <= 1020; i++)
  {
    redVal = calculateVal(stepR, redVal, i);
    grnVal = calculateVal(stepG, grnVal, i);
    bluVal = calculateVal(stepB, bluVal, i);
    DmxSimple.write(reflectorAddress, redVal);
    DmxSimple.write(reflectorAddress + 1, grnVal);
    DmxSimple.write(reflectorAddress + 2, bluVal);

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop
  }

  for (int i = 0; i <= 1020; i++)
  {

    redVal = calculateVal(-stepR, redVal, i);
    grnVal = calculateVal(-stepG, grnVal, i);
    bluVal = calculateVal(-stepB, bluVal, i);
    DmxSimple.write(reflectorAddress, redVal);
    DmxSimple.write(reflectorAddress + 1, grnVal);
    DmxSimple.write(reflectorAddress + 2, bluVal);

    delay(wait); // Pause for 'wait' milliseconds before resuming the loop
  }

  // Update current values for next loop
  prevR = redVal;
  prevG = grnVal;
  prevB = bluVal;
  //delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}

