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
    int uchyb_pion, uchyb_poziom; //uchyb poprzedni do  modułu różniczkującego.
};

#endif // INTELIGENTNE_H
