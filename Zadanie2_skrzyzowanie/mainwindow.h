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
    QHBoxLayout * WindowLayout;
//******************ekran***************//

    QPushButton*  Starter;
    QProgressBar * PasekPostepu;



private slots:
    void start();

signals:
    void postep(int i);
};

#endif // MAINWINDOW_H
