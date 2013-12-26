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

Skrzyzowanie::Skrzyzowanie(int add)
{
    MaxAdd = add;
    SetRandomSeed();
    SetCzasPrzejazdu();
    NaglowekPliku();
    TimeOfService(-1,false,true);
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

Skrzyzowanie::Skrzyzowanie(int gora, int dol, int lewo, int prawo, int add, int przejazd){
    SetRandomSeed();
    SetMaxAdd(add);
    SetStartEntry(gora,dol,lewo,prawo);
    SetCzasPrzejazdu(przejazd);

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
        out.setFieldWidth(3);
        out << "Lp.";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<"#up";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<"#down";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<"#lewo";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<"#prawo";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<"stan";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(10);
        out <<"up.time";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(10);
        out <<"down.time";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(10);
        out <<"left.time";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(10);
        out <<"right.time";
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(10);
        out <<"GreenTime";
        out <<endl;
    }
    file.close();
}

/*!
 * \brief Skrzyzowanie::SetRandomSeed
 *      ustala seed na time(NULL)
 */

void Skrzyzowanie::SetRandomSeed(){
    srand (time(NULL));

}

/*!
 * \brief Skrzyzowanie::SetMaxAdd
 * \param maxadd - maksymalna liczba dodawanych samochodów przy zmianie świateł
 */

void Skrzyzowanie::SetMaxAdd(int maxadd){
    MaxAdd = maxadd;
}

/*!
 * \brief Skrzyzowanie::AddRandomQueues
 *          DOdaje do wszystkich kolejejk skrzyzowania losowe liczby wedlug parametrow klasy skrzyzowanie
 * \param czasoczekiwania - poczatkowa wartosc czasu oczekiwania
 */

void Skrzyzowanie::AddRandomQueues(int czasoczekiwania){
    if(MaxAdd!=0){
        DodajDoKolejki(up, (rand()%MaxAdd), MaxCzasPrzejazdu, MinCzasPrzejazdu, czasoczekiwania);
        DodajDoKolejki(down, (rand()%MaxAdd), MaxCzasPrzejazdu, MinCzasPrzejazdu, czasoczekiwania);
        DodajDoKolejki(left, (rand()%MaxAdd), MaxCzasPrzejazdu, MinCzasPrzejazdu, czasoczekiwania);
        DodajDoKolejki(right, (rand()%MaxAdd), MaxCzasPrzejazdu, MinCzasPrzejazdu, czasoczekiwania);
    }
}

/*!
 * \brief Skrzyzowanie::SetStartEntry
        Dodaje do kolejejek odpowiednie liczby samochodów (do inicjalizacji początkowej - konstruktor
 */

void Skrzyzowanie::SetStartEntry(int gora, int dol, int lewo, int prawo){
    //zainicjowanie kolejek liczbą aut podaną w deklaracji
    DodajDoKolejki(up, gora);
    DodajDoKolejki(down, dol);
    DodajDoKolejki(left, lewo);
    DodajDoKolejki(right, prawo);
}

/*!
 * \brief Skrzyzowanie::SetCzasPrzejazdu
 *          Ustala przedziały czasu obsługi każdego samochodu (wartość minimalna i maksymalna)
 */

void Skrzyzowanie::SetCzasPrzejazdu(int max, int min){
    MaxCzasPrzejazdu = max;
    MinCzasPrzejazdu = min;
}

/*!
 * \brief Skrzyzowanie:: DodajDoKolejki
 *  Dodaje do kolejki określoną ilośc samochodów (domyślnie 1)
 *  używa domyślnego konstruktora klasy Auto
 *
 * \param kolejka - referencja danej kolejki
 * \param n - ile samochodów dodać
 * \param maxCzasPrzejazdu, MinCzasPrzejazdu - Zakres czasu obsługi samochodu
 * \param CzasOczekiwania - poczatkowy czas oczekiwania
 */

void Skrzyzowanie::DodajDoKolejki(queue <Auto> & kolejka, int n, int maxCzasPrzejazdu, int MinCzasPrzejazdu, int CzasOczekiwania){
    for(int i=n;i>0;i--){
        Auto temp(maxCzasPrzejazdu, MinCzasPrzejazdu, CzasOczekiwania);
        kolejka.push(temp);
    }
}

/*!
 * \brief Skrzyzowanie::TimeOfService
 *       Wpisuje do pliku czasy oczekiwania koejnych samochodów.
 *       Ze względu, że nie musimy rozróżniać kierunków świata wszystko idzie do jednego pliczku...
 * \param numer - dana, którą wpisujemy
 * \param endline - czy koniec linii po danej?
 * \param init - Czy usunąć wszystkie dane i zacząc od początku?
 */

void Skrzyzowanie::TimeOfService(int numer, bool endline, bool init){
    QFile file("czasy.txt");
    if (init){
        file.open(QFile::Truncate | QFile::Text| QFile::WriteOnly);
        QTextStream out(&file);
        out<<"iteracja"<<SEPARATOR<<
            "Czasy oczekiwania"<<endl;

    }
    else
    {
        if (file.open(QFile::Append | QFile::Text| QFile::WriteOnly))
        {
            QTextStream out(&file);
            if(numer!=-1){
                out<<numer<<SEPARATOR;
            }
            if(endline){
                out<<endl;
            }
        }
    }
    file.close();
}

/*!
 * \brief Skrzyzowanie::ZapiszDoPliku
 *      Zapisuje co tylko wlezie do pliku wynik.txt
 */

void Skrzyzowanie::ZapiszDoPliku(int IteracjaNum){


    QFile file("wynik.txt");
    if (file.open(QFile::Append | QFile::Text| QFile::WriteOnly))
    {
        QTextStream out(&file);
        out.setFieldWidth(3);
        out << IteracjaNum;
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<up.size();
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<down.size();
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<left.size();
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<right.size();
        out.setFieldWidth(0);
        out << SEPARATOR;
        out.setFieldWidth(5);
        out <<sygnalizator.getKierunek();
        out.setFieldWidth(0);
        out << SEPARATOR;

        Auto temp;
        if(!(up.empty())){
            temp = up.front();
            out.setFieldWidth(10);
            out << temp.GetCzasPrzejazdu();
        }
        else {
            out.setFieldWidth(10);
            out<<'0';
        }
        out.setFieldWidth(0);
        out << SEPARATOR;

        if(!(down.empty())){
            temp = down.front();
            out.setFieldWidth(10);
            out << temp.GetCzasPrzejazdu();
        }
        else {
            out.setFieldWidth(10);
            out<<'0';
        }
        out.setFieldWidth(0);
        out << SEPARATOR;

        if(!(left.empty())){
            temp = left.front();
            out.setFieldWidth(10);
            out << temp.GetCzasPrzejazdu();
        }
        else {
            out.setFieldWidth(10);
            out<<'0';
        }
        out.setFieldWidth(0);
        out << SEPARATOR;

        if(!(right.empty())){
            temp = right.front();
            out.setFieldWidth(10);
            out << temp.GetCzasPrzejazdu();
        }
        else {
            out.setFieldWidth(10);
            out<<'0';
        }
        out.setFieldWidth(0);
        out << SEPARATOR;

        out.setFieldWidth(10);
        out << sygnalizator.getTime();

        out<<endl;
    }

    file.close();
}

/*!
 * \brief Skrzyzowanie::obsluga
 *     Działa, ale trzeba jeszcze dodać obsługę bez świateł oraz z inteligentnymi
 */

void Skrzyzowanie::obsluga(){

    //najpierw mnożymy zmienne
    int temp1, temp2;
    int m=0;
    temp1 = temp2 = sygnalizator.getTime();
    Auto pierwszy, drugi;

    static int iteracjaNum = 0;
    static int CzasObslugi = 0;

    ZapiszDoPliku(iteracjaNum);
    TimeOfService(iteracjaNum, false);

    while((temp1>0)&&(temp2>0)&&(m==0)){
    if(sygnalizator.getKierunek()==pion){
        if(!up.empty()){
            pierwszy = up.front();
            temp1=temp1 - pierwszy.GetCzasPrzejazdu();
            TimeOfService(CzasObslugi+sygnalizator.getTime() - temp1 + pierwszy.GetCzasOczekiwania(), false);
            up.pop();
        }
        else{}

        if(!down.empty()){
            drugi = down.front();
            temp2= temp2 - drugi.GetCzasPrzejazdu();
            TimeOfService(CzasObslugi+sygnalizator.getTime() - temp2 + drugi.GetCzasOczekiwania(), false);
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
            TimeOfService(CzasObslugi+sygnalizator.getTime() - temp1 + pierwszy.GetCzasOczekiwania(), false);
            left.pop();
        }

        if(!right.empty()){
            drugi = right.front();
            temp2-=drugi.GetCzasPrzejazdu();
            TimeOfService(CzasObslugi+sygnalizator.getTime() - temp2 + drugi.GetCzasOczekiwania(), false);
            right.pop();
        }

        if(left.empty()&&right.empty()){
            m=1;
        }
    }
    }
    TimeOfService(-1,true);

    iteracjaNum++;
    sygnalizator.changeKierunek();
    CzasObslugi+=sygnalizator.getTime();
    AddRandomQueues(-CzasObslugi);

}
