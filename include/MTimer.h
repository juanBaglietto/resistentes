#include <TimerOne.h>

#define     LIMPIObANDERA Eventos &= ~i

// --- Eventos
#define     EVENTO0   0 //Evento 0 parpadeo de luz de posicion
#define     EVENTO1   1 //Evento 1 tiempo de duracion de los guinios
#define     EVENTO2   2 //Evento 2 parpadedo de los guinios
#define     EVENTO3   3 //Evento 3 lectura y promedio de acelerometro
#define     EVENTO4   4 //Evento 3 lectura y promedio de acelerometro

#define STEP_FADE      1
#define TIME_FADE      500
#define FREC_DE_GUINIO         5
#define TIEMPO_DE_CLIK         1
#define FREC_BATERIA_BAJA      3
#define     DECIMAS     10
#define     TIMERS      8
#define TIEMPO_BATERIA_BAJA   255



void TmrStart(uint8_t ev, uint8_t t);
void TmrStop(uint8_t ev);
void AnalizarTimer(void);
void TmrEvent(void);