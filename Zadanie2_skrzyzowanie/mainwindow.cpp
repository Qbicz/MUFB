#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "skrzyzowanie.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Skrzyzowanie skrzyzowanie;

    for(int i=0; i<100; i++){
        skrzyzowanie.obsluga();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
