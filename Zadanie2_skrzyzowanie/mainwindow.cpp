#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //początkowe ustawienia okna
    ui->setupUi(this);
    QFont f("Helvetica",10);
    setFont(f);
    setWindowTitle("Skrzyżowanie");

    NazwaPliku= "rozladowanie.txt";

    ui->Starter->setEnabled(false);
    ui->PasekPostepu->setRange(0,100); //to chyba jest nie potrzebne, ale nnie testowałem.

    connect(ui->Starter, SIGNAL(clicked()), this, SLOT(start()));
    connect(this, SIGNAL(postep(int)), ui->PasekPostepu, SLOT(setValue(int)));
    connect(ui->WyborSygnalizacji, SIGNAL(currentIndexChanged(int)), this, SLOT(zmianaTypu(int)));
    connect(ui->Plik, SIGNAL(clicked()), this, SLOT(ustawNazwePliku()));

    zmianaTypu(0); //ukrycie
}

void MainWindow::start()
{
    Skrzyzowanie skrzyzowanie;
    skrzyzowanie.name_rozladowanie = NazwaPliku;
    skrzyzowanie.InitFile(NazwaPliku);



    ustawParametry();

    for(int i = 0;i<100;i++){

    Skrzyzowanie skrzyzowanie(i);                           //inicjacja skrzyżowania z modyfikacja generatora liczb losowych
    //skrzyzowanie.SetInteligence(inteligentna,parametry);    //sterowanie inteligentne z wcześniejszymi parametrami

    skrzyzowanie.name_rozladowanie = NazwaPliku; //nazwa pliku do wpisywania danych

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


    ui->Kd->setEnabled(false);
    ui->Ki->setEnabled(false);

    switch(typ){
    case 0:
    {
        ui->GreenTimeBox->hide();
        ui->GreenTimeLabel->hide();
        ui->Opoznienie->hide();
        ui->OpoznienieLabel->hide();
        ui->Kierunek->hide();
        ui->KierunekLabel->hide();
        ui->Kp->hide();
        ui->KpLabel->hide();
        ui->Kd->hide();
        ui->KdLabel->hide();
        ui->Ki->hide();
        ui->KiLabel->hide();
        ui->Starter->setEnabled(false);
        break;
    }
    case 1:
    {
        ui->GreenTimeBox->show();
        ui->GreenTimeLabel->show();
        ui->Opoznienie->show();
        ui->OpoznienieLabel->show();
        ui->Kierunek->show();
        ui->KierunekLabel->show();
        ui->Kp->hide();
        ui->KpLabel->hide();
        ui->Kd->hide();
        ui->KdLabel->hide();
        ui->Ki->hide();
        ui->KiLabel->hide();
        ui->Starter->setEnabled(true); //uruchamiamy opcje symulacji tylko jeśli wybrana jest któraś sygnalizacja
        break;
    }
    case 2:
    {
        ui->GreenTimeBox->show();
        ui->GreenTimeLabel->show();
        ui->Opoznienie->show();
        ui->OpoznienieLabel->show();
        ui->Kierunek->show();
        ui->KierunekLabel->show();
        ui->Kp->show();
        ui->KpLabel->show();
        ui->Kd->show();
        ui->KdLabel->show();
        ui->Ki->show();
        ui->KiLabel->show();
        ui->Starter->setEnabled(true); //uruchamiamy opcje symulacji tylko jeśli wybrana jest któraś sygnalizacja
        break;
    }

    default:
        zmianaTypu(0);
        break;
    }
}

void MainWindow::ustawParametry()
{
    parametry = new int[6];

    //parametry sygnalizacji

    parametry[0] = ui->GreenTimeBox->value();      //greenTime
    parametry[1] = ui->Opoznienie->value();       //opóźnienie
    parametry[2] = ui->Kierunek->currentIndex();    //kierunek


    //wszystkie współczynniki podanie sa *1000
    parametry[3] = ui->Kp->value();        //Kp;
    parametry[4] = ui->Kd->value();           //Kd;
    parametry[5] = ui->Ki->value();         //Ki;


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

