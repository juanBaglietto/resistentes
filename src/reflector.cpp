#include "reflector.h"
#include <DmxSimple.h>

void Reflector::initReflector(int address)
{
    _address = address;
    _crossFade.setAddress(_address);
}

void Reflector::setColor(Color color)
{

    _color.changeColor(color.getRed(), color.getGreen(), color.getBlue());
    DmxSimple.write(_address, color.getRed());
    DmxSimple.write(_address + 1, color.getGreen());
    DmxSimple.write(_address + 2, color.getBlue());
}

void Reflector::setStatus(bool status)
{

    _status = status;
    if (_status)
    {
        setColor(_color);
    }
    else
    {

        DmxSimple.write(_address, 0);
        DmxSimple.write(_address + 1, 0);
        DmxSimple.write(_address + 2, 0);
    }
}

void Reflector::equal(Reflector R1)
{

    _address = R1._address;
    _color = R1._color;
    _status = R1._status;
}

void Reflector::initCrossFade()
{
    _crossFade.crossFade(_color);
}
