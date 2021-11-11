#include "MTimer.h"
#include "reflector.h"

volatile uint8_t TmrRun[TIMERS];
volatile uint8_t Eventos = 0;
extern Reflector reflector1;
extern Reflector reflector2;
extern Reflector *reflectorSelec;
int segundo=0;
// funciones de timer
//******************************************************************************************
//  Proposito: Lanzamientos de Timers.
//  Parametros:
//                  ev : Numero de Timer
//                  t : valor de Timer.
//  Retorna: void.
//******************************************************************************************
void TmrStart(uint8_t ev, uint8_t t)
{ //void TmrStart(EVENTO ev,TIEMPO t)
    noInterrupts();
    if (t)
    {
        TmrRun[ev] = t;
        Eventos &= ~((uint8_t)0x01 << ev);
    }
    else
    {
        TmrRun[ev] = 0;
        Eventos &= ~((uint8_t)0x01 << ev);
    }
    interrupts();
}

//******************************************************************************************
//  Proposito: Apaga todo los timers
//  Parametros: void
//  Retorna: void.
//******************************************************************************************
void TmrClose(void)
{
    uint8_t i;
    noInterrupts();
    for (i = 0; i < TIMERS; i++)
        TmrRun[i] = 0;
    Eventos = 0;
    interrupts();
}

//*******************************************************************************************
//  Proposito: Apaga un timer en particular
//  Parametros: void
//  Retorna: void.
//*******************************************************************************************
void TmrStop(uint8_t ev)
{
    noInterrupts();
    TmrRun[ev] = 0;
    Eventos &= ~((uint8_t)0x01 << ev);

    interrupts();
}

//*******************************************************************************************
//  Proposito: Analiza Eventos de timers. No es una primitiva. Es parte o toda la aplicaciÃ³n
//        La ubico en este .c para tener todas las funciones de timers juntas.
//  Parametros: void.
//  Retorna: void.
//*******************************************************************************************
void TmrEvent(void)
{
    uint8_t i;
    for (i = 0x01; i; i <<= 1)
    {
        switch (Eventos & i)
        {
        case 0x01: //venciÃ³ EVENTO0   // interrucion cada 5 mseg
            LIMPIObANDERA;
            break;

        case 0x02: //venciÃ³ EVENTO1
            reflectorSelec->_crossFade.setFadeStatus(FADE_OUT);
            
            //TmrStart(EVENTO2, TIME_FADE);
            LIMPIObANDERA;
            break;

        case 0x04: //venciÃ³ EVENTO2
            //TmrStart(EVENTO1, TIME_FADE);
            //digitalWrite(LED_BUILTIN, LOW);
            //reflector1._crossFade.setFadeStatus(0);
            LIMPIObANDERA;

            break;

        case 0x08: //venciÃ³ EVENTO3

            LIMPIObANDERA;
            break;

        case 0x10: //case 0x10

            LIMPIObANDERA;
            break;

        case 0x20: //case 0x20
            LIMPIObANDERA;
            break;

        case 0x40: //case 0x40
            LIMPIObANDERA;
            break;

        case 0x80: //case 0x80
            LIMPIObANDERA;
            break;
        }
    }
}

//******************************************************************************************
//  Proposito:  Descuento de Timers. No es una primitiva. Es una funciÃ³n de la capa inferior.
//        La ubico en este .c para tener todas las funciones de timers juntas.
//  Parametros:
//                  Ev : Numero de Timer
//  Retorna: void.

void AnalizarTimer(void)
{
    uint8_t i;

    if (segundo >= SEGUNDO)
    {

        segundo=0;
        for (i = 0; i < TIMERS; i++)
        {
            if (TmrRun[i])
            {
                TmrRun[i]--;

                if (!TmrRun[i])
                {
                    noInterrupts();
                    Eventos |= ((uint8_t)0x01 << i);
                    interrupts();
                }
            }
        }
        
    }
    segundo++;
}