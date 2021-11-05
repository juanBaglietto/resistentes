#include "color.h"

void Color::changeColor(int red, int green, int blue)
{
    _red=red;
    _green=green;
    _blue=blue;
}

int Color::getRed()
{
    return _red;
}

int Color::getGreen()
{
    return _green;
}

int Color::getBlue()
{
    return _blue;
}