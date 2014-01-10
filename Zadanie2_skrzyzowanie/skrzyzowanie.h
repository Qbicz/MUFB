#ifndef SKRZYZOWANIE_H
#define SKRZYZOWANIE_H
#include "auto.h"
#include "sygnalizator.h"
#include "staloczasowy.h"
#include "inteligentne.h"

#include <QString>

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

enum Inteligence {brak=0, staloczasowa=1, inteligentna=2};

class Skrzyzowanie
{
public:
    Skrzyzowanie(int mnoznik =1);
    Skrzyzowanie(int gora, int dol, int lewo, int prawo, int add = 3, int przejazd = 3);
    void SetInteligence(Inteligence a, int* parameters);
    void SetStartEntry(int gora, int dol, int lewo, int prawo);
    void SetMaxAdd(int maxadd = 3);
    void SetCzasPrzejazdu(int max = 3, int min = 1);
    void obsluga();

    void SaveFile(int numer, bool endline, QString name);
    void InitFile(QString name);

    bool rozladowanie; //czy już jest rozladowany
    QString name_rozladowanie;

private:
    queue <Auto> up, down, left, right;
    Sygnalizator * sygnalizator;
    unsigned int MaxAdd; //maksymalna ilość dodanych aut
    int MaxCzasPrzejazdu, MinCzasPrzejazdu;
    int MaxCzasOczekiwania;
    unsigned int CzasObslugi;
    unsigned int iteracjaNum;

    void AddRandomQueues(int czasoczekiwania = 0);
    void DodajDoKolejki(queue <Auto> & kolejka, int n=1, int maxczasprzejazdu = 3, int minczasprzejazdu = 1, int czasoczekiwania = 0);
    void SetRandomSeed(int mnoznik = 1);
    void ZapiszDoPliku(int IteracjaNum);
    void NaglowekPliku();

    //nazwy plików
    QString name_czasy;


};

#endif // SKRZYZOWANIE_H
