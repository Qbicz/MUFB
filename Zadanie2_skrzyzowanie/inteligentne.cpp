#include "inteligentne.h"

Inteligentne::Inteligentne()
{
    greenTime = 30;
    redTime = 30;
    state = red;
    kierunek = pion;
    opoznienie = 0;
    proporcjonalny = 1;
}

int Inteligentne::getTime(){
    return greenTime - opoznienie;
}

void Inteligentne::setParameters(int *parameters){
    greenTime = parameters[0];
    opoznienie = parameters[1];
    kierunek = (Kierunek)parameters[2];

}

void Inteligentne::obsluga(int *dane){
    greenTime = greenTime*2;
    changeKierunek();
}
