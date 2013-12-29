#ifndef STALOCZASOWY_H
#define STALOCZASOWY_H
#include"sygnalizator.h"

//Stałoczasowy typ sygnalizatora:
/*POsiada:
 *
 *
 *
 **/

class Staloczasowy : public Sygnalizator
{
public:
    Staloczasowy();
    Staloczasowy(unsigned long time);
    void setParameters(int *parameters);
    void obsluga(int *dane = NULL);
};

#endif // STALOCZASOWY_H
