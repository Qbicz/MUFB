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
    SygnalizacjaLayout= new QFormLayout;

    QWidget * mycentralwidget = new QWidget;
    mycentralwidget->setLayout(WindowLayout);

    this->setCentralWidget(mycentralwidget);
    this->setWindowTitle("Skrzyżowanie");

    NazwaPliku= "rozladowanie.txt";


    Starter= new QPushButton("START");
    Plik= new QPushButton("Zmień nazwę pliku");
    Starter->setEnabled(false);
    WyborSygnalizacji = new QComboBox;




    QHBoxLayout* Layout1 = new QHBoxLayout();
      Layout1->addWidget(Starter);

      PasekPostepu = new QProgressBar;
      PasekPostepu->setRange(0,100);
      Layout1->addWidget(PasekPostepu);

      QHBoxLayout* Layout2 = new QHBoxLayout();

      Layout2->addWidget(Plik);
      Plik->setMaximumWidth(200);


      QHBoxLayout* Layout3 = new QHBoxLayout();

      WyborSygnalizacji->addItem("Brak");
      WyborSygnalizacji->addItem("Stałoczasowa");
      WyborSygnalizacji->addItem("Inteligentna");
      WyborSygnalizacji->setMaximumWidth(200);
      QLabel* EtykietaSyg= new QLabel("Wybierz typ sygnalizacji: ");
      Layout3->addWidget(EtykietaSyg);
      Layout3->addWidget(WyborSygnalizacji);



     WindowLayout->addLayout(Layout1);
     WindowLayout->addLayout(Layout2);
     WindowLayout->addLayout(Layout3);

    connect(Starter, SIGNAL(clicked()), this, SLOT(start()));
    connect(this, SIGNAL(postep(int)), PasekPostepu, SLOT(setValue(int)));
    connect(WyborSygnalizacji, SIGNAL(currentIndexChanged(int)), this, SLOT(zmianaTypu(int)));
    connect(Plik, SIGNAL(clicked()), this, SLOT(ustawNazwePliku()));


}

void MainWindow::start()
{
    Skrzyzowanie skrzyzowanie;
    skrzyzowanie.InitFile(NazwaPliku);

    ustawParametry();

    for(int i = 0;i<100;i++){

    Skrzyzowanie skrzyzowanie(i);                           //inicjacja skrzyżowania z modyfikacja generatora liczb losowych
    //skrzyzowanie.SetInteligence(inteligentna,parametry);    //sterowanie inteligentne z wcześniejszymi parametrami


    if(i%5==0){
        //n+=1;
        //parametry[3]+=100;                        // zwiekszenie czasu zielonego o 5 co 5 iteracji
    }

//tutaj bedze zamiast TypSwiatel zamiast staloczasowa!
    skrzyzowanie.SetInteligence((Inteligence)TypSwiatel,parametry);  //sterowanie stałoczasowe z wcześniejszymi parametrami
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

void MainWindow::zmianaTypu(int typ){
    //gdzie zgodnie z enum Intelligence mamy 0-brak (ale to wykluczam)  1-staloczasowa i 2 inteligentna


    if( typ<0 || typ>2)
        return; //ale to i tak sie nie zdarzy

    if(typ!=0) //jeśli typ==0 mozemy nie zmieniac typu
        TypSwiatel=typ;

    GreenTimeBox= new QSpinBox;
    Opoznienie= new QSpinBox;
    Kierunek = new QComboBox;
    Kp = new QSpinBox;
    Kd = new QSpinBox;
    Ki = new QSpinBox;

    GreenTimeBox->setMinimum(10);
    GreenTimeBox->setMaximum(50);
    GreenTimeBox->setValue(30);

    Opoznienie->setMinimum(0);
    Opoznienie->setMaximum(10);

    Opoznienie->setValue(2);

    Kierunek->addItem("pion"); //0
    Kierunek->addItem("poziom"); //1


    Kp->setMinimum(1000);
    Kp->setMaximum(2000);
    Kp->setValue(1400);

    Kp->setEnabled(false);

    Kd->setMinimum(0);
    Kd->setMaximum(1000);
    Kd->setValue(0);


    Ki->setMinimum(0);
    Ki->setMaximum(1000);
    Ki->setValue(0);

    Ki->setEnabled(false);

    if(typ==0)
        Starter->setEnabled(false); // jesli nie ma wybranej sygnalizacji wyłączamy opcję symulacji


    if(typ==1 || typ ==2){

    Starter->setEnabled(true); //uruchamiamy opcje symulacji tylko jeśli wybrana jest któraś sygnalizacja

        if(SygnalizacjaLayout->rowCount() ==0){

            SygnalizacjaLayout->addRow("Czas światła zielonego: ",GreenTimeBox);
            SygnalizacjaLayout->addRow("Opóźnienie: ",Opoznienie);
            SygnalizacjaLayout->addRow("Kierunek:",Kierunek);

        }

        if(typ !=2){

            WindowLayout->addLayout(SygnalizacjaLayout);
        }


        if(typ == 2 && SygnalizacjaLayout->rowCount() != 6){

            SygnalizacjaLayout->addRow("Kp:",Kp);
            SygnalizacjaLayout->addRow("Kd: ",Kd);
            SygnalizacjaLayout->addRow("Ki: ",Ki);

            cout<<SygnalizacjaLayout->rowCount();

            WindowLayout->addLayout(SygnalizacjaLayout);

        }

    }

//jeśli liczba obiektów powinna się zmienić usuwam SygnalizacjaLayout i widgety
//tworze od nowa i obiekty (poprzez malutką rekurencję)
    if((SygnalizacjaLayout->rowCount() ==6 && typ != 2) || (SygnalizacjaLayout->rowCount() ==3 && typ == 0)){
        QLayoutItem * item;
        QWidget * widget;

        while ((item = SygnalizacjaLayout->takeAt(0))) {

            if ((widget = item->widget()) != 0) {
                widget->hide();
                delete widget;
            }
            else {
                delete item;
            }
        }

        delete SygnalizacjaLayout;
        SygnalizacjaLayout= new QFormLayout;

        zmianaTypu(typ);

    }

}

void MainWindow::ustawParametry()
{
    parametry = new int[6];

    //parametry sygnalizacji

    parametry[0] = GreenTimeBox->value();      //greenTime
    parametry[1] = Opoznienie->value();       //opóźnienie
    parametry[2] = Kierunek->currentIndex();    //kierunek


    //wszystkie współczynniki podanie sa *1000
    parametry[3] = Kp->value();        //Kp;
    parametry[4] = Kd->value();           //Kd;
    parametry[5] = Ki->value();         //Ki;


}

void MainWindow::ustawNazwePliku()
{

    bool ok;
    QString text = QInputDialog::getText(this,
                                         tr("Zmiana nazwy pliku"),
                                         tr("Wpisz nazwę pliku wynikowego z .txt na końcu: "),
                                         QLineEdit::Normal,
                                         NazwaPliku,
                                         &ok);
    if(ok)
        NazwaPliku=text;

}


MainWindow::~MainWindow()
{
    delete ui;
}

