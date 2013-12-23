#include "skrzyzowanie.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

#include <QFile>
#include <QTextStream>

//SEPARATOR danych w pliku
#define SEPARATOR ','

using namespace std;

/*!
 * \brief Skrzyzowanie::Skrzyzowanie
 *      Domyślny konstruktok klasy skrzyżowanie - jeszcze nic nie robi...
 *      maxadd - zmienna, która określa maksymalną ilość aut dodawanych do kolejki
 */

Skrzyzowanie::Skrzyzowanie(int m = 3)
{
    maxadd = m;
    SetRandomSeed();
    //zainicjowanie kolejek losową liczbą aut
    DodajDoKolejki(up, rand()%maxadd);
    DodajDoKolejki(down, rand()%maxadd);
    DodajDoKolejki(left, rand()%maxadd);
    DodajDoKolejki(right, rand()%maxadd);
}

/*!
 * \brief Skrzyzowanie::Skrzyzowanie
 *      Zaawansowany konstruktor
 * \param gora
 * \param dol
 * \param lewo
 * \param prawo
 *      Liczba samochodów na starcie w danym kierunku
 * \param add
 *      Ile max aut dodać przy zmianie świateł?
 * \param przejazd
 *      Ile maksymalnie czasu auto zajmuje na skrzyzowaniu
 */

Skrzyzowanie::Skrzyzowanie(int gora, int dol, int lewo, int prawo, int add = 3, int przejazd = 3){
    maxadd = add;
    SetRandomSeed();
    //zainicjowanie kolejek liczbą aut podaną w deklaracji
    DodajDoKolejki(up, gora, przejazd);
    DodajDoKolejki(down, dol, przejazd);
    DodajDoKolejki(left, lewo, przejazd);
    DodajDoKolejki(right, prawo, przejazd);

    NaglowekPliku();
}

/*!
 * \brief Skrzyzowanie::NaglowekPliku
 *      Tu nie potrzeba opisu.
 *      SEPARATOR - do plików csv to przecinek.
 */

void Skrzyzowanie::NaglowekPliku(){
    //nagłówek pliku
    QFile file("wynik.txt");
    if (file.open(QFile::Text | QFile::Truncate | QFile::WriteOnly))
    {
        QTextStream out(&file);
        out << "Lp."<<SEPARATOR<<
               "#up"<<SEPARATOR<<
               "#down"<<SEPARATOR<<
               "#lewo"<<SEPARATOR<<
               "#prawo"<<SEPARATOR<<
               "stan"<<SEPARATOR<<
               "up.time"<<SEPARATOR<<
               "down.time"<<SEPARATOR<<
               "left.time"<<SEPARATOR<<
               "right.time"<<SEPARATOR<<
               "GreenTime"<<SEPARATOR<<
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

void Skrzyzowanie::DodajDoKolejki(queue <Auto> & kolejka, int n, int maxTime){
    for(int i=n;i>0;i--){
        Auto temp(maxTime);
        kolejka.push(temp);
    }
}

/*!
 * \brief Skrzyzowanie::ZapiszDoPliku
 *      Zapisuje co tylko wlezie do pliku wynik.txt
 */

void Skrzyzowanie::ZapiszDoPliku(){

    static int iteracjaNum = 0;
    QFile file("wynik.txt");
    if (file.open(QFile::Append | QFile::Text| QFile::WriteOnly))
    {
        QTextStream out(&file);
        out << iteracjaNum<<SEPARATOR<<
               up.size()<<SEPARATOR<<
               down.size()<<SEPARATOR<<
               left.size()<<SEPARATOR<<
               right.size()<<SEPARATOR<<
               sygnalizator.getKierunek()<<SEPARATOR;

        Auto temp;
        if(!(up.empty())){
            temp = up.front();
            out << temp.GetCzasPrzejazdu()<<SEPARATOR;
        }
        else {
            out<<'0'<<SEPARATOR;
        }
        if(!(down.empty())){
            temp = down.front();
            out << temp.GetCzasPrzejazdu()<<SEPARATOR;
        }
        else {
            out<<'0'<<SEPARATOR;
        }
        if(!(left.empty())){
            temp = left.front();
            out << temp.GetCzasPrzejazdu()<<SEPARATOR;
        }
        else {
            out<<'0'<<SEPARATOR;
        }
        if(!(right.empty())){
            temp = right.front();
            out << temp.GetCzasPrzejazdu()<<SEPARATOR;
        }
        else {
            out<<'0'<<SEPARATOR;
        }
        out<<sygnalizator.getTime()<<SEPARATOR;

        out<<endl;
    }
    iteracjaNum++;
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
    int m=0;
    temp1 = temp2 = sygnalizator.getTime();
    Auto pierwszy, drugi;

    ZapiszDoPliku();

    while(((temp1>0)||(temp2>0))&&(m==0)){
    if(sygnalizator.getKierunek()==pion){
        if(!up.empty()){
            pierwszy = up.front();
            temp1-=pierwszy.GetCzasPrzejazdu();
            up.pop();
        }
        else{}

        if(!down.empty()){
            drugi = down.front();
            temp2-=drugi.GetCzasPrzejazdu();
            down.pop();
        }
        else{}

        if(down.empty()&&up.empty()){
            m=1;
        }
    }
    else {
        if(!left.empty()){
            pierwszy = left.front();
            temp1-=pierwszy.GetCzasPrzejazdu();
            left.pop();
        }

        if(!right.empty()){
            drugi = right.front();
            temp2-=drugi.GetCzasPrzejazdu();
            right.pop();
        }

        if(left.empty()&&right.empty()){
            m=1;
        }
    }

    //testy tempów:
    //cout<<"Temp1: "<<temp1<<endl;
    //cout<<"Temp2: "<<temp2<<endl;
    }

    sygnalizator.changeKierunek();

    DodajDoKolejki(up, (rand()%maxadd));
    DodajDoKolejki(down, (rand()%maxadd));
    DodajDoKolejki(left, (rand()%maxadd));
    DodajDoKolejki(right, (rand()%maxadd));


}
