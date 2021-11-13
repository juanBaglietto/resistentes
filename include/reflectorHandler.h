#include "reflector.h"

#define MAXIMO_REFLECTORES 6

class ReflectorHandler
{
private:
    Reflector *reflectores[MAXIMO_REFLECTORES];
    byte reflectoresEnUso=0;

public:
    ReflectorHandler();
    void addReflector(Reflector *ref);
    Reflector* getReflector(byte num_ref);
    byte getCantReflectoresEnUso();
    
};
