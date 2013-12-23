#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skrzyzowanie.h"

#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    Skrzyzowanie skrzyzowanie(1000,100,0,0,5,10);

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
