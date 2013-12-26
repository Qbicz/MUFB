#ifndef AUTO_H
#define AUTO_H

//klasa opisująca samochody
/*! Posiada:
 * czas przejazdu (generowany losowo)
 **/

class Auto
{
public:
    Auto(int max = 3, int min = 1, int CzasOczekiwania = 0);
    int GetCzasPrzejazdu();
    void Reset();
    int GetCzasOczekiwania();
    void SetCzasOczekiwania(int a);
    ~Auto();

private:
    int czas_przejazdu;
    int czas_oczekiwania;
};

#endif // AUTO_H
