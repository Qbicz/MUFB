#include <time.h>
#include "sygnalizator.h"

Sygnalizator::Sygnalizator(unsigned long greenT,
                           unsigned long redT)
    : state(red), greentime(greenT), redtime(redT)
{
    this->wykonaj_stan();
}

~Sygnalizator()
{

}

getState()
{
    return state;
}
change()
{
    if(state == red)
        state = green;
    else
        state = red;
}

wykonaj_stan()
{
    if(state == green)
        Sleep(greenTime);
    else Sleep(redTime);
    change();
}
