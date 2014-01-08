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

//******************ekran***************//

    QPushButton*  Starter;
    QProgressBar * PasekPostepu;
    QComboBox * WyborSygnalizacji;



private slots:
    void start();
    void zmianaTypu(int typ);

signals:
    void postep(int i);
};

#endif // MAINWINDOW_H
