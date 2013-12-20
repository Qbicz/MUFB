#ifndef AUTO_H
#define AUTO_H

//klasa opisująca samochody
/*POsiada:
 * czas przejazdu (generowany losowo)
 *
 *
 **/

class Auto
{
public:
    Auto(); //konstruktor bez seeda
    Auto(int max); //konstruktor z generatorem i wartością maksymalną (generator inicjalizowany wcześniej)
private:
    int czas_przejazdu;
};

#endif // AUTO_H
