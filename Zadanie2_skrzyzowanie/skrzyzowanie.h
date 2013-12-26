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

enum Inteligence {brak, staloczasowa, inteligentna};

class Skrzyzowanie
{
public:
    Skrzyzowanie(int m = 3);
    Skrzyzowanie(int gora, int dol, int lewo, int prawo, int add = 3, int przejazd = 3);
    void SetInteligence(Inteligence a);
    void SetStartEntry(int gora, int dol, int lewo, int prawo);
    void SetMaxAdd(int maxadd = 3);
    void SetCzasPrzejazdu(int max = 3, int min = 1);
    void obsluga();

private:
    queue <Auto> up, down, left, right;
    Sygnalizator sygnalizator;
    int MaxAdd; //maksymalna ilość dodanych aut
    int MaxCzasPrzejazdu, MinCzasPrzejazdu;


    void AddRandomQueues(int czasoczekiwania = 0);
    void DodajDoKolejki(queue <Auto> & kolejka, int n=1, int maxczasprzejazdu = 3, int minczasprzejazdu = 1, int czasoczekiwania = 0);
    void SetRandomSeed();
    void ZapiszDoPliku(int IteracjaNum);
    void NaglowekPliku();

    void TimeOfService(int numer, bool endline = true, bool init = false);

};

#endif // SKRZYZOWANIE_H
