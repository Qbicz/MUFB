#include <time.h>
#include "sygnalizator.h"

Sygnalizator::Sygnalizator(unsigned long greenT,
                           unsigned long redT)
    : state(red), greenTime(greenT), redTime(redT)
{
    this->wykonaj_stan();
}

Sygnalizator::~Sygnalizator()
{
    greenTime = 30;
    redTime = 30;
    state = red;
}

State Sygnalizator::getState()
{
    return state;
}
void Sygnalizator::change()
{
    if(state == red)
        state = green;
    else
        state = red;
}

void Sygnalizator::wykonaj_stan()
{
    /*if(state == green) //nie będziemy czekali na zdarzenie tylko odejmowali od pozostalego czasu czas przejazdu
        sleep(greenTime);
    else sleep(redTime);
    */
    change();
}
