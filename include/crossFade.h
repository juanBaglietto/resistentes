
#include <DmxSimple.h>
#include <Arduino.h>
#include "color.h"
enum RefStatus
{
    ESPERA_CF,
    INICIO_CF,
    FADE_IN,
    FULL,
    FADE_OUT,
    FIN_CF
};
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

    RefStatus reflector_status;
    int t_fade_in = 0;
    int t_fade_out = 0;
    int t_fade = 0;

    int fade_delay_r;
    int fade_delay_g;
    int fade_delay_b;

public:
    void setAddress(byte adr);
    void crossFade(Color color);
    int fadeIn();
    int fadeOut();
    void countFadeUp();
    void setcountFade(int value);
    int getTcountFade();
    void setFadeStatus(RefStatus st);
    RefStatus getFadeStatus();
    void setTFadeIn(int);
    int getTFadeIn();
    void setTFadeOut(int);
    int getTFadeOut();
    void setTFade(int);
    int getTFade();
    int getFadeDelay_b();
};
