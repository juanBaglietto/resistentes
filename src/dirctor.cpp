#include "director.h"

Director::Director()
{

    actualState = SCENE_1;
    statusE1 = E1_FIN;
    statusE2 = E2_FIN;
}
void Director::init(ReflectorHandler *refs)
{
    reflectors = refs;
}
void Director::setScene(Allscenes sceneActual)
{
    actualState = sceneActual;
}

Allscenes Director::getScene()
{
    return actualState;
}
void Director::updateScenes()
{
    switch (actualState)
    {
    case SCENE_1:
        if (statusE1 == E1_FIN)
        {
            statusE1 = E1_INICIO;
        }
        updateScene_1();
        break;
    case SCENE_2:
        updateScene_2();
        break;
    case SCENE_3:
        updateScene_3();
        break;

    default:
        break;
    }
}

void Director::updateScene_1()
{
    switch (statusE1)
    {
    case E1_INICIO:
        reflectors->getReflector(0)->setReflectorStatus(INICIO_CF);
        statusE1 = E1_PASO_1;
        break;
    case E1_PASO_1:
        if (reflectors->getReflector(0)->getReflectorStatus() == FADE_OUT && reflectors->getReflector(0)->getPercentFadeOut() >= 90)
        {
            reflectors->getReflector(1)->setReflectorStatus(INICIO_CF);
            statusE1 = E1_PASO_2;
        }
        break;
    case E1_PASO_2:
        if (reflectors->getReflector(1)->getReflectorStatus() == FADE_OUT && reflectors->getReflector(1)->getPercentFadeOut() >= 50)
        {
            statusE1 = E1_INICIO;
        }
        break;
    case E1_PASO_3:
        break;
    case E1_PASO_4:
        break;
    case E1_PASO_5:
        break;
    case E1_PASO_6:
        break;
    case E1_FIN:
        break;

    default:
        break;
    }
}

void Director::updateScene_2()
{
    switch (statusE2)
    {
    case E2_INICIO:
        reflectors->getReflector(0)->setReflectorStatus(INICIO_CF);
        reflectors->getReflector(1)->setReflectorStatus(INICIO_CF);
        statusE2 = E2_PASO_1;
        break;
    case E2_PASO_1:
        if (reflectors->getReflector(1)->getReflectorStatus() == FADE_OUT && reflectors->getReflector(1)->getPercentFadeOut() >= 90)
        {
            reflectors->getReflector(2)->setReflectorStatus(INICIO_CF);
            reflectors->getReflector(3)->setReflectorStatus(INICIO_CF);
            statusE2 = E2_PASO_2;
        }
        break;
    case E2_PASO_2:
        if (reflectors->getReflector(3)->getReflectorStatus() == FADE_OUT && reflectors->getReflector(3)->getPercentFadeOut() >= 50)
        {
            statusE2 = E2_INICIO;
        }
        break;
    case E2_PASO_3:
        break;
    case E2_PASO_4:
        break;
    case E2_PASO_5:
        break;
    case E2_PASO_6:
        break;
    case E2_FIN:
        break;

    default:
        break;
    }
}

void Director::updateScene_3()
{
}
