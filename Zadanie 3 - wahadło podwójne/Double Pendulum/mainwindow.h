#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QVector>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    //QWidget *centralWidget;
    ~MainWindow();
    void setupSincScatterDemo(QCustomPlot *customPlot);
    void setupScatterStyleDemo(QCustomPlot *customPlot);
    int setupxy(QCustomPlot *customPlot, int num);
    int setupxt(QCustomPlot *customPlot, int num);
    int setupyt(QCustomPlot *customPlot, int num);
    int setupfit(QCustomPlot *customPlot, int num);
    int setupomegat(QCustomPlot *customPlot, int num);
    int setupfifi(QCustomPlot *customPlot, int num);

    //void trajektoria(QCustomPlot *customPlot);
    
public slots:
    void realtimexy();
    void realtimext();
    void realtimeyt();
    void realtimefit();
    void realtimeomegat();
    void realtimefifi();
    //void trajektoriaSlot();
    void odbierzdane(QVector<qreal> &);
    void wykresxy();
    void wykresxt();
    void wykresyt();
    void wykresfit();
    void wykresomegat();
    void wykresfifi();

signals:
    void czasact(const QString &);
    void fi1act(const QString &);
    void fi2act(const QString &);
    void omega1act(const QString &);
    void omega2act(const QString &);


private:
    Ui::MainWindow *ui;
    QString demoName;
    QTimer dataTimer;
    QCPItemTracer *itemDemoPhaseTracer;
    int currentDemoIndex;
    QVector<qreal> wektor;
    int num;

    QCPCurve *Curve;

};

#endif // MAINWINDOW_H

