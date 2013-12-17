#ifndef SKRZYZOWANIE_H
#define SKRZYZOWANIE_H
#include "auto.h"
#include "sygnalizator.h"

//klasa opisująca cały mechanizm skrzyżowania.
/*Posiada:
 *4x FIFO (której to klasy jeszcze nie ma)
 *1x sygnalizator
 *
 *
 *
 */


class Skrzyzowanie
{
public:
    Skrzyzowanie();

private:
    Auto up, down, left, right;
    Sygnalizator sygnalizator;
    void obsluga();
};

#endif // SKRZYZOWANIE_H
