#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skrzyzowanie.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    Skrzyzowanie skrzyzowanie;
    skrzyzowanie.InitFile("rozladowanie.txt");

    //parametry sygnalizacji
    int parametry[6];
    parametry[0] = 30;      //greenTime
    parametry[1] = 2;       //opóźnienie
    parametry[2] = pion;    //kierunek


    //wszystkie współczynniki podanie sa *1000
    parametry[3] = 1400;        //Kp;
    parametry[4] = 0;           //Kd;
    parametry[5] = 0;         //Ki;

    int n=0;

    for(int i = 0;i<100;i++){

    Skrzyzowanie skrzyzowanie(i);                           //inicjacja skrzyżowania z modyfikacja generatora liczb losowych
    //skrzyzowanie.SetInteligence(inteligentna,parametry);    //sterowanie inteligentne z wcześniejszymi parametrami


    if(i%5==0){
        //n+=1;
        //parametry[3]+=100;                        // zwiekszenie czasu zielonego o 5 co 5 iteracji
    }


    skrzyzowanie.SetInteligence(staloczasowa,parametry);  //sterowanie stałoczasowe z wcześniejszymi parametrami
    skrzyzowanie.SetCzasPrzejazdu(5,1);         //ustalenie
    skrzyzowanie.SetMaxAdd(5);                  //ile samochodów pojawia się po zmianie czasu w każdej kolejce
    skrzyzowanie.SetStartEntry(100,0,1,0);    //wejściowy skok
    cout<<i<<endl;                              //wypisz numer iteracji - dla orientacji, czy program działa

    int j=0;
    while(!skrzyzowanie.rozladowanie)           //wykonuj, aż skrzyżowanie się nie "rozładuje"
    {
        skrzyzowanie.obsluga();                 //magia
        //cerr<<j<<endl;
        j++;
    }

    }

    ui->setupUi(this);                          //po zakończeniu wyświetl puste okienko, które nic nie robi...

}

MainWindow::~MainWindow()
{
    delete ui;
}
