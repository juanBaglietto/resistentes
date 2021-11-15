#include "reflectorHandler.h"


ReflectorHandler::ReflectorHandler()
{}

void ReflectorHandler::addReflector(Reflector *ref)
{
    reflectors[reflectorsEnUso]=ref;
    reflectorsEnUso++;
}


Reflector* ReflectorHandler::getReflector(byte num_ref)
{
 return reflectors[num_ref];
}

byte ReflectorHandler::getCantReflectoresEnUso()
{
    return reflectorsEnUso;
}

void ReflectorHandler::UpdateAllReflectors()
{
    for (byte i = 0; i <= reflectorsEnUso; i++)
    {
       reflectors[i]->updateStatus();
    }
    
}