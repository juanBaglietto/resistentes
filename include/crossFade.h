
#include <DmxSimple.h>
#include <Arduino.h>
#include "color.h"

class CrossFade
{
private:
    int calculateVal(int step, int val, int i);
    int calculateStep(int prevValue, int endValue);

    int redVal = 0;
    int grnVal = 0;
    int bluVal = 0;

    int prevR = redVal;
    int prevG = grnVal;
    int prevB = bluVal;
    int wait = 5;

    int reflectorAddress;
    

public:
    void setAddress(int adr);
    void crossFade(Color color);
};

