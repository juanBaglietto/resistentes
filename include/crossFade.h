
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

    int stepR = 0;
    int stepG = 0;
    int stepB = 0;
    int countFade=0;
    
    int reflectorAddress;
    int fadeStatus=0;

public:
    
    void setAddress(int adr);
    void crossFade(Color color);
    void fadeIn();
    void fadeOut();
    void countFadeUp();
    void setcountFade(int value);
    void setFadeStatus(int);
    int getFadeStatus();
};
