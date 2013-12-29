#include "staloczasowy.h"

Staloczasowy::Staloczasowy()
{
    greenTime = 30;
    redTime = 30;
    state = red;
    kierunek = pion;
    opoznienie = 0;
}

Staloczasowy::Staloczasowy(unsigned long time){
    greenTime = time;
    state = red;
    kierunek = pion;
    opoznienie = 0;
}

void Staloczasowy::setParameters(int *parameters){
    greenTime = parameters[0];
    opoznienie = parameters[1];
    kierunek = (Kierunek)parameters[2];
}
void Staloczasowy::obsluga(int *dane){
    changeKierunek();
}
