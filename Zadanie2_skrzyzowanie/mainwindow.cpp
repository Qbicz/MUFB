#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                          //po zakończeniu wyświetl puste okienko, które nic nie robi...
    QFont f("Helvetica",10);
    this->setFont(f);

    WindowLayout= new QVBoxLayout;

    QWidget * mycentralwidget = new QWidget;
    mycentralwidget->setLayout(WindowLayout);

    this->setCentralWidget(mycentralwidget);
    this->setWindowTitle("Skrzyżowanie");


    Starter= new QPushButton("START");
    WyborSygnalizacji = new QComboBox;


    QHBoxLayout* Layout1 = new QHBoxLayout();
      Layout1->addWidget(Starter);

      PasekPostepu = new QProgressBar;
      PasekPostepu->setRange(0,100);
      Layout1->addWidget(PasekPostepu);

      QHBoxLayout* Layout2 = new QHBoxLayout();

      WyborSygnalizacji->addItem("Brak");
      WyborSygnalizacji->addItem("Stałoczasowa");
      WyborSygnalizacji->addItem("Inteligentna");
      WyborSygnalizacji->setMaximumWidth(200);
      QLabel* EtykietaSyg= new QLabel("Wybierz typ sygnalizacji: ");

      Layout2->addWidget(EtykietaSyg);
      Layout2->addWidget(WyborSygnalizacji);

     WindowLayout->addLayout(Layout1);
     WindowLayout->addLayout(Layout2);

    connect(Starter, SIGNAL(clicked()), this, SLOT(start()));
    connect(this, SIGNAL(postep(int)), PasekPostepu, SLOT(setValue(int)));
    connect(WyborSygnalizacji, SIGNAL(currentIndexChanged(int)), this, SLOT(zmianaTypu(int)));


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

//tutaj bedze zamiast TypSwiatel zamiast staloczasowa!
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

void MainWindow::zmianaTypu(int typ)
{
    //gdzie zgodnie z enum Intelligence mamy 0-brak 1-staloczasowa i 2 inteligentna

    //jeśli typ==0 mozemy nie zmieniac typu

    TypSwiatel=typ; //sama zmiana zmiennej nie wywola od nowa funkcji z niej korzystającej!
    //trzeba dalej emitowac sygnaly ktore by zmienily reszta :(

    //tutaj mogą się znaleźć opcje wykluczajace poszczegolne ustawienia
    //jesli rozne typy sygnalizacji korzystaja z roznych parametrow
}


MainWindow::~MainWindow()
{
    delete ui;
}

