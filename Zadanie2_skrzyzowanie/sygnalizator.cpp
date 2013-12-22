#include <time.h>
#include "sygnalizator.h"

Sygnalizator::Sygnalizator(unsigned long greenT,
                           unsigned long redT)
    : state(red), kierunek(pion), greenTime(greenT), redTime(redT)
{
    //this->wykonaj_stan();
}

Sygnalizator::Sygnalizator()
{
    greenTime = 30;
    redTime = 30;
    state = red;
    kierunek = pion;
}

Sygnalizator::~Sygnalizator()
{
}

State Sygnalizator::getState()
{
    return state;
}

Kierunek Sygnalizator::getKierunek()
{
    return kierunek;
}

int Sygnalizator::getTime()
{
    return greenTime;
}

void Sygnalizator::setTime(int time)
{
    greenTime = time;
}


void Sygnalizator::changeState()
{
    if(state == red)
        state = green;
    else
        state = red;
}

void Sygnalizator::changeKierunek()
{
    if(kierunek == pion)
        kierunek = poziom;
    else
        kierunek = pion;
}

