#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skrzyzowanie.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                          //po zakończeniu wyświetl puste okienko, które nic nie robi...
    QFont f("Helvetica",10);
    this->setFont(f);

    WindowLayout= new QHBoxLayout;

    QWidget * mycentralwidget = new QWidget;
    mycentralwidget->setLayout(WindowLayout);

    this->setCentralWidget(mycentralwidget);
    this->setWindowTitle("Skrzyżowanie");


    Starter= new QPushButton("START");

    QHBoxLayout* Layout = new QHBoxLayout();
      Layout->addWidget(Starter);

      PasekPostepu = new QProgressBar;
      PasekPostepu->setRange(0,100);
      Layout->addWidget(PasekPostepu);
     WindowLayout->addLayout(Layout);

    connect(Starter, SIGNAL(clicked()), this, SLOT(start()));
    connect(this, SIGNAL(postep(int)), PasekPostepu, SLOT(setValue(int)));


}

void MainWindow::start()
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
    emit postep(i);                              //wypisz numer iteracji - dla orientacji, czy program działa

    int j=0;
    while(!skrzyzowanie.rozladowanie)           //wykonuj, aż skrzyżowanie się nie "rozładuje"
    {
        skrzyzowanie.obsluga();                 //magia
        //cerr<<j<<endl;
        j++;
    }


    }
    emit postep(100);
}


MainWindow::~MainWindow()
{
    delete ui;
}

