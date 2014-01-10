#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSpacerItem>
#include <QGroupBox>
#include <QWidget>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QProgressBar>
#include <QComboBox>
#include <QInputDialog>
#include <QString>


#include "skrzyzowanie.h"

#include <iostream>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVBoxLayout * WindowLayout;
    int TypSwiatel;
    int * parametry;
    void ustawParametry();
    QString NazwaPliku;


//******************ekran***************//

    QPushButton*  Starter;
    QPushButton*  Plik;
    QProgressBar * PasekPostepu;
    QComboBox * WyborSygnalizacji;


    QFormLayout * SygnalizacjaLayout;
    QSpinBox * GreenTimeBox;
    QSpinBox * Opoznienie;
    QComboBox *Kierunek;
    QSpinBox * Kp;
    QSpinBox * Kd;
    QSpinBox * Ki;



private slots:
    void start();
    void zmianaTypu(int typ);
    void ustawNazwePliku();


signals:
    void postep(int i);
};

#endif // MAINWINDOW_H
