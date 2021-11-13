#include "reflectorHandler.h"


ReflectorHandler::ReflectorHandler()
{}

void ReflectorHandler::addReflector(Reflector *ref)
{
    reflectores[reflectoresEnUso]=ref;
    reflectoresEnUso++;
}


Reflector* ReflectorHandler::getReflector(byte num_ref)
{
 return reflectores[num_ref];
}

byte ReflectorHandler::getCantReflectoresEnUso()
{
    return reflectoresEnUso;
}