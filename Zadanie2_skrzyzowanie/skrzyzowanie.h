#ifndef SKRZYZOWANIE_H
#define SKRZYZOWANIE_H
#include "auto.h"
#include "sygnalizator.h"

/*!
 *plik nagłówkowy kolejek FIFO (działa jak wektor)
 *podiada:
 *  void push( const TYP_DANYCH & wartosc ); (dodaj na koniec),
 *  void pop();(wyrzuć z począku)
 *  bool empty() const;(czy pusty?)
 *  size_type size() const; (wielkość)
 *  TYP_DANYCH & front() (pierwszy)
 *  TYP_DANYCH & back(); (ostatni)
 *
 **/
#include <queue>


using namespace std;

/*!
 * \brief The Skrzyzowanie class
 *      Zawiera cały skomplikowany mechanizm obsługi skrzyżowania:
 *      4x kolejka FIFO
 *      1x sygnalizator (steruje ruchem pion, poziom)
 *      1x max - maksymalna liczba aut dodanych za jednym razem do każdej z kolejek
 *      1x publiczna funkja obsługa, która robi wszystko - magic.
 */


class Skrzyzowanie
{
public:
    Skrzyzowanie(int m = 3);
    void obsluga();

private:
    queue <Auto> up, down, left, right;
    Sygnalizator sygnalizator;
    int max;

    void DodajDoKolejki(queue <Auto> & kolejka, int n=1);
    void SetRandomSeed();
    void ZapiszDoPliku();
};

#endif // SKRZYZOWANIE_H
