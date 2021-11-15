#include "reflectorHandler.h"
enum Allscenes
{
  SCENE_1,
  SCENE_2,
  SCENE_3,
} ;



enum Scene1
{
  E1_INICIO,
  E1_PASO_1,
  E1_PASO_2,
  E1_PASO_3,
  E1_PASO_4,
  E1_PASO_5,
  E1_PASO_6,
  E1_FIN,
} ;



enum Scene2
{
  E2_INICIO,
  E2_PASO_1,
  E2_PASO_2,
  E2_PASO_3,
  E2_PASO_4,
  E2_PASO_5,
  E2_PASO_6,
  E2_FIN,
} ;


class Director
{
private: 

    Allscenes actualState;
    Scene1 statusE1;
    Scene2 statusE2;
    ReflectorHandler *reflectors;
public:
    Director();
    void init(ReflectorHandler *refs);
    void updateScenes();
    void updateScene_1();
    void updateScene_2();
    void updateScene_3();
    void setScene(Allscenes sceneActual);
    Allscenes getScene();
};
