#include "skrzyzowanie.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>


#include <QFile>
#include <QTextStream>

//SEPARATOR danych w pliku
#define SEPARATOR ','
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))


using namespace std;

/*!
 * \brief Skrzyzowanie::Skrzyzowanie
 *      Domyślny konstruktok klasy skrzyżowanie - jeszcze nic nie robi...
 *      mnoznik - tylko i wylacznie do usuniecia efektu zbyt szybkiego programu i małej liczby liczb losowych...
 */

Skrzyzowanie::Skrzyzowanie(int mnoznik)
{
    name_czasy = "czasy.txt";
    name_rozladowanie = "rozladowanie.txt";
    MaxAdd = 3;
    SetRandomSeed(mnoznik);
    SetCzasPrzejazdu();
    NaglowekPliku();
    InitFile(name_czasy);
    rozladowanie =false;
    CzasObslugi = 0;
    iteracjaNum = 0;
    MaxCzasOczekiwania = 0;
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
    rozladowanie =false;
    NaglowekPliku();
    name_czasy = "czasy.txt";
    name_rozladowanie = "rozladowanie.txt";
    InitFile(name_czasy);
    CzasObslugi = 0;
    iteracjaNum = 0;
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
        out.setFieldWidth(8);
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

void Skrzyzowanie::SetRandomSeed(int mnoznik){
    srand (time(NULL) *mnoznik);

}

/*!
 * \brief Skrzyzowanie::SetMaxAdd
 * \param maxadd - maksymalna liczba dodawanych samochodów przy zmianie świateł
 */

void Skrzyzowanie::SetMaxAdd(int maxadd){
    MaxAdd = maxadd;
}

void Skrzyzowanie::SetInteligence(Inteligence a, int * parameters){
    switch (a)
    {
        case staloczasowa:
            {
                sygnalizator  = new Staloczasowy;
                break;
            }

    case inteligentna :
    {
        sygnalizator = new Inteligentne;
        break;
    }
    case brak:
    {
        break;
    }
    default:
    {
        break;
    }
    }

    sygnalizator->setParameters(parameters);
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
 * \brief Skrzyzowanie::InitFile
 *      To miała być funkcja inicjalizująca nagłówki w plikach, ale coś szwankuje
 * \param name - nazwa pliku
 */

void Skrzyzowanie::InitFile(QString name){
    QFile file(name);
    if (file.open(QFile::Truncate | QFile::Text | QFile::WriteOnly))
        {
            QTextStream out(&file);
            if (name == name_czasy){
                out<<"Iteracja"<<SEPARATOR<<"Czasy ozekiwania"<<endl;
            }
            if (name == name_rozladowanie){
                out<<"Rozladowanie po 'x' iteracjach"<<SEPARATOR<<"Max Czas Oczekiwania"
                  <<SEPARATOR<<"Sredni czas zielonego" <<SEPARATOR<<"Czas obslugi"<<endl;
            }

        }
    file.close();
}

/*!
 * \brief Skrzyzowanie::SaveFile
 *      Funkcja wpisująca do pliku dane - TU JEST GDZIEŚ BŁĄD (typu dzielenie przez 0, bo wywala aplikację, a nie blędy)
 * \param numer - liczba jaką wpiszemy do pliku
 * \param endline - czy koniec linii
 * \param name - nazwa
 */

void Skrzyzowanie::SaveFile(int numer, bool endline, QString name){

    QFile file(name);
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

        out.setFieldWidth(9);
        if (sygnalizator->getKierunek() == pion){
            out <<"pion";
        }
        else{
            out<<"poziom";
        }

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
        out << sygnalizator->getTime();

        out<<endl;
    }

    file.close();
}

/*!
 * \brief Skrzyzowanie::obsluga
 *      Działa, ale trzeba jeszcze dodać obsługę bez świateł oraz z inteligentnymi
 */

void Skrzyzowanie::obsluga(){

    //obsługa światał przede wszystkim
    int dane[4];
    dane[0] = up.size();
    dane[1] = down.size();
    dane[2] = left.size();
    dane[3] = right.size();

    sygnalizator->obsluga(dane);

    // mnożymy zmienne
    int temp1, temp2;
    int m=0;
    temp1 = temp2 = sygnalizator->getTime() - sygnalizator->opoznienie; //zmienne określające czas podczas przejazdu aut (przejazd auto to czas zielonego - opóż nienie
    Auto pierwszy, drugi;
    int AktualnyCzasOczekiwania;

    ZapiszDoPliku(iteracjaNum);
    SaveFile(iteracjaNum, false, name_czasy);



    //pętelka na światła:

    while((temp1>0)&&(temp2>0)&&(m==0)){ // warunek końca przejazdu samochodów
    if(sygnalizator->getKierunek()==pion){
        if(!up.empty()){
            pierwszy = up.front();
            AktualnyCzasOczekiwania = CzasObslugi+sygnalizator->getTime() - temp1 + pierwszy.GetCzasOczekiwania();
            SaveFile(AktualnyCzasOczekiwania, false, name_czasy);
            temp1=temp1 - pierwszy.GetCzasPrzejazdu();
            MaxCzasOczekiwania = MAX(MaxCzasOczekiwania,AktualnyCzasOczekiwania);
            up.pop();
        }
        else{}

        if(!down.empty()){
            drugi = down.front();
            AktualnyCzasOczekiwania = CzasObslugi+sygnalizator->getTime() - temp2 + drugi.GetCzasOczekiwania();
            SaveFile(AktualnyCzasOczekiwania, false, name_czasy);
            temp2-=drugi.GetCzasPrzejazdu();
            MaxCzasOczekiwania = MAX(MaxCzasOczekiwania,AktualnyCzasOczekiwania);
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
            AktualnyCzasOczekiwania = CzasObslugi+sygnalizator->getTime() - temp1 + pierwszy.GetCzasOczekiwania();
            SaveFile(AktualnyCzasOczekiwania, false, name_czasy);
            temp1=temp1 - pierwszy.GetCzasPrzejazdu();
            MaxCzasOczekiwania = MAX(MaxCzasOczekiwania,AktualnyCzasOczekiwania);
            left.pop();
        }

        if(!right.empty()){
            drugi = right.front();
            AktualnyCzasOczekiwania = CzasObslugi+sygnalizator->getTime() - temp2 + drugi.GetCzasOczekiwania();
            SaveFile(AktualnyCzasOczekiwania, false, name_czasy);
            temp2-=drugi.GetCzasPrzejazdu();
            MaxCzasOczekiwania = MAX(MaxCzasOczekiwania,AktualnyCzasOczekiwania);
            right.pop();
        }

        if(left.empty()&&right.empty()){
            m=1;
        }
    }
    }

    //zakończ linię w pliku czasy.txt
    SaveFile(-1,true, name_czasy);

    iteracjaNum++;
    //cerr<<iteracjaNum<<endl;

    //obsługa czasu obsługi
    CzasObslugi+=sygnalizator->getTime();
    AddRandomQueues(-CzasObslugi);

    //warunek rozładowania skrzyżowania
    if((up.size()<=MaxAdd)&&(down.size()<=MaxAdd)&&(left.size()<=MaxAdd)&&(right.size()<=MaxAdd)){
        rozladowanie = true;
        //iteracjaNum++;
        ZapiszDoPliku(iteracjaNum);
        SaveFile(iteracjaNum,false,name_rozladowanie);
        SaveFile(MaxCzasOczekiwania, false, name_rozladowanie);
        int SredniGreenTime = CzasObslugi/(iteracjaNum);
        SaveFile(SredniGreenTime, false, name_rozladowanie);
        SaveFile(CzasObslugi,true, name_rozladowanie);

    }

}
