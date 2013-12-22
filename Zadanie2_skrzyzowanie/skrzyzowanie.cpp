#include "skrzyzowanie.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <QFile>
#include <QTextStream>

//SEPARATOR danych w pliku
#define SEPARATOR ','

using namespace std;

/*!
 * \brief Skrzyzowanie::Skrzyzowanie
 *      Domyślny konstruktok klasy skrzyżowanie - jeszcze nic nie robi...
 *      max - zmienna, która określa maksymalną ilość aut dodawanych do kolejki
 */

Skrzyzowanie::Skrzyzowanie(int m)
{
    max = m;
    SetRandomSeed();
    //zainicjowanie kolejek losową liczbą aut
    DodajDoKolejki(up, rand()%max);
    DodajDoKolejki(down, rand()%max);
    DodajDoKolejki(left, rand()%max);
    DodajDoKolejki(right, rand()%max);

    //nagłówek pliku
    QFile file("wynik.txt");
    if (file.open(QFile::Text | QFile::Truncate | QFile::WriteOnly))
    {
        QTextStream out(&file);
        out << "czas"<<SEPARATOR<<
               "up"<<SEPARATOR<<
               "down"<<SEPARATOR<<
               "lewo"<<SEPARATOR<<
               "prawo"<<SEPARATOR<<
               "stan"<<SEPARATOR<<
               endl;
    }

}

/*!
 * \brief Skrzyzowanie::SetRandomSeed
 *      ustala seed na time(NULL)
 */

void Skrzyzowanie::SetRandomSeed(){
    srand (time(NULL));

}

/*!
 * \brief Skrzyzowanie:: DodajDoKolejki
 *  Dodaje do kolejki określoną ilośc samochodów (domyślnie 1)
 *  używa domyślnego konstruktora klasy Auto
 *
 * \param kolejka - referencja danej kolejki
 * \param n - ile samochodów dodać
 */

void Skrzyzowanie::DodajDoKolejki(queue <Auto> & kolejka, int n){
    for(int i=n;i>0;i--){
        Auto temp;
        kolejka.push(temp);
    }
}

/*!
 * \brief Skrzyzowanie::ZapiszDoPliku
 *      Zapisuje co tylko wlezie do pliku wynik.txt
 */

void Skrzyzowanie::ZapiszDoPliku(){

    QFile file("wynik.txt");
    if (file.open(QFile::Append | QFile::Text))
    {
        QTextStream out(&file);
        out << sygnalizator.getTime()<<SEPARATOR<<
               up.size()<<SEPARATOR<<
               down.size()<<SEPARATOR<<
               left.size()<<SEPARATOR<<
               right.size()<<SEPARATOR<<
               sygnalizator.getKierunek()<<SEPARATOR<<
               endl;
    }
    file.close();
}

/*!
 * \brief Skrzyzowanie::obsluga
 *      magia - komentarze dodam w miarę tworzenia
 *      stan na dziś:
 *      - działa przełączanie stanów
 *      - pliki chyba chodzą ok
 *      nie działa:
 *      - usuwanie aut (nie wiem, czy dodawanie działa dobrze)
 */

void Skrzyzowanie::obsluga(){

    //najpierw mnożymy zmienne
    int temp1, temp2;
    temp1 = temp2 = sygnalizator.getTime();
    Auto pierwszy, drugi;

    while((temp1<0)||(temp2<0)){
    if(sygnalizator.getKierunek()==pion){
        pierwszy = up.front();
        drugi = down.front();
        temp1-=pierwszy.GetCzasPrzejazdu();
        temp2-=drugi.GetCzasPrzejazdu();
        up.pop();
        down.pop();
    }
    else {
        pierwszy = left.front();
        drugi = right.front();
        temp1-=pierwszy.GetCzasPrzejazdu();
        temp2-=drugi.GetCzasPrzejazdu();
        left.pop();
        right.pop();
    }
    }
    ZapiszDoPliku();

    sygnalizator.changeKierunek();

    DodajDoKolejki(up, rand()%max);
    DodajDoKolejki(down, rand()%max);
    DodajDoKolejki(left, rand()%max);
    DodajDoKolejki(right, rand()%max);


}
