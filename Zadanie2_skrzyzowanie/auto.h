#ifndef AUTO_H
#define AUTO_H

//klasa opisująca samochody
/*! Posiada:
 * czas przejazdu (generowany losowo)
 **/

class Auto
{
public:
    Auto(int max = 3);
    int GetCzasPrzejazdu();

private:
    int czas_przejazdu;
};

#endif // AUTO_H
