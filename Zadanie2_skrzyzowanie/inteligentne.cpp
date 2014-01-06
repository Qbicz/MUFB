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
    calka_pion = 0;
    calka_poziom = 0;
    greenTime_poziom = greenTime;
    greenTime_pion = greenTime;
    uchyb_pop = 0;
    Kp = 1;
    Kd = 0;
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
    unsigned int pionowo = dane[0] + dane[1];
    unsigned int poziomo = dane[2] + dane[3];
    unsigned int uchyb = 0;


    if (kierunek==pion){
        uchyb = pionowo;
        calka_pion += (uchyb+uchyb_pop)*greenTime/2;
        //cout<<"pion:"<<uchyb_pop_pion<<" "<<calka_pion<<endl;
        greenTime = Kp/1000*(uchyb   +    Ki*calka_pion/1000   +    Kd*(uchyb - uchyb_pop)/(greenTime*1000));
        uchyb_pop_pion = uchyb;
        greenTime_pion = greenTime;

    }
    else{
        uchyb = poziomo;
        calka_poziom += (uchyb+uchyb_pop)*greenTime/2;
        //cout<<"poziom:"<<calka_poziom<<endl;
        greenTime = Kp/1000*(uchyb   +   Ki*calka_poziom/1000   +   Kd*(uchyb - uchyb_pop)/(greenTime*1000));
        uchyb_pop_poziom = uchyb;
        greenTime_poziom = greenTime;
    }
    uchyb_pop = uchyb;

    //cerr<<uchyb<<endl;
}
