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
    parametry[0] = 10;      //greenTime
    parametry[1] = 2;       //opóźnienie
    parametry[2] = pion;    //kierunek

    parametry[3] = 1500;      //Kp;
    parametry[4] = 1;        //Kd;
    parametry[5] = 1;        //Ki;

    for(int i = 0;i<100;i++){

    Skrzyzowanie skrzyzowanie(i);
    //skrzyzowanie.SetInteligence(inteligentna,parametry);
    if(i%5==0){
        parametry[0]+=5;
    }
    skrzyzowanie.SetInteligence(staloczasowa,parametry);
    skrzyzowanie.SetCzasPrzejazdu(5,1);
    skrzyzowanie.SetMaxAdd(5);
    skrzyzowanie.SetStartEntry(120,100,20,0);
    cout<<i<<endl;

    int j=0;
    while(!skrzyzowanie.rozladowanie)
    {
        skrzyzowanie.obsluga();
        //cerr<<j<<endl;
        j++;
    }

    }

    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
