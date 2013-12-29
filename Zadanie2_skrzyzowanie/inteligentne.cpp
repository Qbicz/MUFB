#include "inteligentne.h"
#include <iostream>
using namespace std;

Inteligentne::Inteligentne()
{
    greenTime = 30;
    redTime = 30;
    state = red;
    kierunek = pion;
    opoznienie = 0;
    Kp = 1;
    Kd = 1;
    Ki = 0;
}

int Inteligentne::getTime(){
    return greenTime - opoznienie;
}

void Inteligentne::setParameters(int *parameters){
    greenTime = parameters[0];
    opoznienie = parameters[1];
    kierunek = (Kierunek)parameters[2];

    Kp = parameters[3];
    Kd = parameters[4];
    Ki = parameters[5];

}

void Inteligentne::obsluga(int *dane){
    changeKierunek();
    int pionowo = dane[0] + dane[1];
    int poziomo = dane[2] + dane[3];
    int uchyb = 0;

    if (kierunek==pion){
        uchyb = pionowo;
    }
    else{
        uchyb = poziomo;
    }

    //cerr<<uchyb<<endl;

    greenTime = Kp*(uchyb)/1000;// + Kd*((uchyb - uchyb_pop)/czas) + (1/Ki)*calka(uchyb));

    if (kierunek==pion){
        uchyb_pion = pionowo;
    }
    else{
        uchyb_poziom = poziomo;
    }
}
