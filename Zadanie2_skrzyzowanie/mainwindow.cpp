#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skrzyzowanie.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    Skrzyzowanie skrzyzowanie;
    skrzyzowanie.SetCzasPrzejazdu(5,1);
    skrzyzowanie.SetMaxAdd(5);
    skrzyzowanie.SetStartEntry(120,100,20,0);


    for(int i=0; i<100; i++){
        skrzyzowanie.obsluga();
        cout<<i<<endl;
    }
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}
