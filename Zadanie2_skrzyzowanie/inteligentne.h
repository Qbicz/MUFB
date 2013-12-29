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
    int proporcjonalny;
};

#endif // INTELIGENTNE_H
