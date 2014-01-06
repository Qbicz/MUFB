#ifndef INTELIGENTNE_H
#define INTELIGENTNE_H
#include"sygnalizator.h"

//Inteligentny typ sygnalizatora:
/*POsiada:
 *
 *
 *
 **/

class Inteligentne : public Sygnalizator
{
public:
    Inteligentne();
    int getTime();
    void setParameters(int *parameters);
    void obsluga(int *dane);
    //wspołłczynniki:
private:
    int Kp,Kd,Ki;
    unsigned int uchyb_pop_pion, uchyb_pop_poziom, uchyb_pop; //uchyb poprzedni do  modułu różniczkującego.
    unsigned long int calka_pion, calka_poziom;  //zmienna całkująca
    unsigned long int greenTime_pion, greenTime_poziom ;
};

#endif // INTELIGENTNE_H
