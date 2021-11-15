
#define ADDRESS_BASE_REFL_1 1
#define ADDRESS_BASE_REFL_2 7
#define ADDRESS_BASE_REFL_3 13
#define ADDRESS_BASE_REFL_4 20

#define STEP_FADE_IN_ms 1
#define STEP_FADE_OUT_ms 1
#define DELAY_FULL 1
#include "crossFade.h"
#include "MTimer.h"
enum ReflectorStatus
{
    ESPERA_CF,
    INICIO_CF,
    FADE_IN,
    FULL,
    FADE_OUT,
    FIN_CF
};
class Reflector
{
private:
    Color _color;
    bool reflectorOn;
    byte _address;
    ReflectorStatus reflectorStatus;
    CrossFade crossFade;

public:
    
    Reflector()
    {
       _address=0; 
    }
    void initReflector(byte address);
    void setColor(Color color);
    void manualOnOff(bool on);
    bool isReflectorOn();
    void setReflectorStatus(ReflectorStatus refStatus);
    ReflectorStatus getReflectorStatus();
    void updateStatus();
    void setTimeCrossFade(int t_in,int t_full,int t_out);
    int getPercentFadeOut();
};
