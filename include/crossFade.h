
#include <DmxSimple.h>
#include <Arduino.h>
#include "color.h"

class CrossFade
{
private:
    int calculateVal(int step, int val, int i);
    long calculateStep(int prevValue, int endValue);

    int redVal = 0;
    int grnVal = 0;
    int bluVal = 0;

    int col_R = 0;
    int col_G = 0;
    int col_B = 0;

    int prevR = redVal;
    int prevG = grnVal;
    int prevB = bluVal;
    int wait = 5;

    long stepR = 0;
    long stepG = 0;
    long stepB = 0;
    int countFade = 0;

    byte reflectorAddress;


    int t_fade_in = 0;
    int t_fade_out = 0;
    int t_fade_full = 0;

    int percentFadeOut=0;

public:
    void setAddress(byte adr);
    void crossFade(Color color);
    int fadeIn();
    int fadeOut();
    void setcountFade(int value);
    int getTcountFade();
    void setTFadeIn(int);
    int getTFadeIn();
    void setTFadeOut(int);
    int getTFadeOut();
    void setTFadeFull(int);
    int getTFadeFull();
    int getFadeDelay_b();
    int getPercentFadeOut();
};
