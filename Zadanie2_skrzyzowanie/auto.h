#ifndef AUTO_H
#define AUTO_H

//klasa opisująca samochody
/*! Posiada:
 * czas przejazdu (generowany losowo)
 **/

class Auto
{
public:
    Auto(int max = 3, int min = 1);
    int GetCzasPrzejazdu();
    void Reset();

private:
    int czas_przejazdu;
};

#endif // AUTO_H
