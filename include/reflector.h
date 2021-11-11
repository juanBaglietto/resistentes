
#define ADDRESS_BASE_REFL_1 1
#define ADDRESS_BASE_REFL_2 7
#define ADDRESS_BASE_REFL_3 13
#define ADDRESS_BASE_REFL_4 20
#include "crossFade.h"

class Reflector
{
private:
    Color _color;
    
    byte _address;
    bool _status;


public:
    CrossFade _crossFade;
    Reflector()
    {
       _address=0; 
       _status=false;
    }
    void initReflector(byte address);
    void setColor(Color color);
    void setStatus(bool status);
    bool getStatus();
    void equal(Reflector R1);
    void initCrossFade();
};
