#include <QtGui>
//#include <QApplication>
//#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#define PI 3.14


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TIMER
    QTimer *timer = new QTimer(this);
    timer->setInterval (50);
    connect(timer, SIGNAL(timeout()), ui->widget, SLOT(animate()));

    //sloty
        //przyciski
    connect(ui->starter, SIGNAL(clicked()),  timer, SLOT(start()));
    connect(ui->stoper, SIGNAL(clicked()),  timer, SLOT(stop()));
    connect(ui->starter, SIGNAL(clicked()),  &dataTimer, SLOT(start()));
    connect(ui->stoper, SIGNAL(clicked()),  &dataTimer, SLOT(stop()));

    connect(ui->quit,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->reset, SIGNAL(clicked()), ui->widget, SLOT(reset()));
    connect(ui->reset, SIGNAL(clicked()),  timer, SLOT(stop()));
    connect(ui->reset, SIGNAL(clicked()),  &dataTimer, SLOT(stop()));

        //inne
    connect(ui->m1Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setm1(const QString &)));
    connect(ui->m2Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setm2(const QString &)));
    connect(ui->l1Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setl1(const QString &)));
    connect(ui->l2Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setl2(const QString &)));
    connect(ui->fi10Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setfi10(const QString &)));
    connect(ui->fi20Edit, SIGNAL(textChanged(const QString &)), ui->widget, SLOT(setfi20(const QString &)));

    //sygnały

    connect(ui->widget, SIGNAL(dane(QVector<qreal> &)),this, SLOT(odbierzdane(QVector<qreal> &)));
    connect(this, SIGNAL(czasact(const QString&)), ui->czas2, SLOT(setText(const QString &)));
    connect(this, SIGNAL(fi1act(const QString&)), ui->fi1Read, SLOT(setText(const QString &)));
    connect(this, SIGNAL(fi2act(const QString&)), ui->fi2Read, SLOT(setText(const QString &)));
    connect(this, SIGNAL(omega1act(const QString&)), ui->omega1Read, SLOT(setText(const QString &)));
    connect(this, SIGNAL(omega2act(const QString&)), ui->omega2Read, SLOT(setText(const QString &)));

    //Walidatory
    QIntValidator * masa = new QIntValidator(0, 100000);
    ui->m1Edit->setValidator(masa);
    ui->m2Edit->setValidator(masa);
    QIntValidator * dlugosc = new QIntValidator(0, 20000);
    ui->l1Edit->setValidator(dlugosc);
    ui->l2Edit->setValidator(dlugosc);
    QIntValidator * kat = new QIntValidator(-360,360);
    ui->fi10Edit->setValidator(kat);
    ui->fi20Edit->setValidator(kat);


    //wybór wykresów
    connect(ui->yx, SIGNAL(pressed()), this, SLOT(wykresxy())); //1
    connect(ui->xt, SIGNAL(pressed()), this, SLOT(wykresxt())); //2
    connect(ui->yt, SIGNAL(pressed()), this, SLOT(wykresyt())); //3
    connect(ui->fit, SIGNAL(pressed()), this, SLOT(wykresfit())); //4
    connect(ui->omegat, SIGNAL(pressed()), this, SLOT(wykresomegat())); //5
    connect(ui->fifi, SIGNAL(pressed()), this, SLOT(wykresfifi())); //6

    ui->yx->click();
    Curve = new QCPCurve(ui->customplot->xAxis, ui->customplot->yAxis);

    setWindowTitle("Double Pendulum");
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::odbierzdane(QVector<qreal> & a){
    wektor = a;
    QVector <qreal> ::iterator iter = wektor.begin();

    emit czasact(QString::number(iter[0],'f',2));
    emit fi1act(QString::number(iter[5]*180/PI,'f',2));
    emit fi2act(QString::number(iter[6]*180/PI,'f',2));
    emit omega1act(QString::number(iter[7],'f',2));
    emit omega2act(QString::number(iter[8],'f',2));

}

void MainWindow::wykresxy(){
    num=1;
    //setupScatterStyleDemo(ui->customplot);
    num = setupxy(ui->customplot, num);
    //setupSincScatterDemo(ui->customplot2);
    //setWindowTitle("QCustomPlot: "+demoName);
    statusBar()->clearMessage();
    ui->customplot->replot();

}

void MainWindow::wykresxt(){
    num=2;
    num = setupxt(ui->customplot, num);
    statusBar()->clearMessage();
    ui->customplot->replot();
}

void MainWindow::wykresyt(){
    num=3;
    num = setupyt(ui->customplot, num);
    statusBar()->clearMessage();
    ui->customplot->replot();
}

void MainWindow::wykresfit(){
    num=4;
    num = setupfit(ui->customplot, num);
    statusBar()->clearMessage();
    ui->customplot->replot();
}

void MainWindow::wykresomegat(){
    num=5;
    num = setupomegat(ui->customplot, num);
    statusBar()->clearMessage();
    ui->customplot->replot();
}

void MainWindow::wykresfifi(){
    num=6;
    num = setupfifi(ui->customplot, num);
    statusBar()->clearMessage();
    ui->customplot->replot();

}

int MainWindow::setupfifi(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=6;

  if(num!=a){
      return num;
  }

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));


  Curve->clearData();
  Curve->setPen(QPen(Qt::blue));
  Curve->setLineStyle(QCPCurve::lsLine);
  Curve->setAntialiasedFill(true);

  customPlot->addPlottable(Curve); // blue line

  customPlot->addGraph(); // blue dot
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->graph(0)->setAntialiasedFill(true);

  ui->customplot->graph(0)->clearData();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;
}

void MainWindow::realtimefifi()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[7];
#endif
    qreal value0 = iter[8];

    // add data to lines:
    Curve->addData(key0, value0);
    // set data of dots:
    ui->customplot->graph(0)->clearData();
    ui->customplot->graph(0)->addData(key0, value0);
    // remove data of lines that's outside visible range:
    Curve->removeDataBefore(key0-6);
    //przeskalowanie

  ui->customplot->yAxis->setRange(value0+3, 6, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0+3, 6, Qt::AlignRight);
  ui->customplot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}

int MainWindow::setupomegat(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=5;

  if(num!=a){
      return num;
  }

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
  customPlot->graph(0)->setAntialiasedFill(true);

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->graph(1)->setAntialiasedFill(true);

  customPlot->addGraph(); // red line
  customPlot->graph(2)->setPen(QPen(Qt::red));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssNone);

  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);


  ui->customplot->graph(0)->clearData();
  ui->customplot->graph(1)->clearData();
  ui->customplot->graph(2)->clearData();
  ui->customplot->graph(3)->clearData();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;
}

void MainWindow::realtimeomegat()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[0];
    qreal key1 = iter[0];
#endif
    qreal value0 = iter[7];
    qreal value1 = iter[8];
    // add data to lines:
    ui->customplot->graph(0)->addData(key0, value0);
    ui->customplot->graph(2)->addData(key1, value1);
    // set data of dots:
    ui->customplot->graph(1)->clearData();
    ui->customplot->graph(1)->addData(key0, value0);
    ui->customplot->graph(3)->clearData();
    ui->customplot->graph(3)->addData(key1, value1);
    // remove data of lines that's outside visible range:
    ui->customplot->graph(0)->removeDataBefore(key0-8);
    ui->customplot->graph(2)->removeDataBefore(key1-8);
    //przeskalowanie
    //ui->customplot->graph(0)->rescaleValueAxis(true);
    //ui->customplot->graph(2)->rescaleValueAxis(true);

  ui->customplot->yAxis->setRange(value0/2+value1/2+2, 4, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0+1, 8, Qt::AlignRight);
  ui->customplot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}

int MainWindow::setupfit(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=4;

  if(num!=a){
      return num;
  }

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
  customPlot->graph(0)->setAntialiasedFill(true);

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->graph(1)->setAntialiasedFill(true);

  customPlot->addGraph(); // red line
  customPlot->graph(2)->setPen(QPen(Qt::red));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssNone);

  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  ui->customplot->graph(0)->clearData();
  ui->customplot->graph(1)->clearData();
  ui->customplot->graph(2)->clearData();
  ui->customplot->graph(3)->clearData();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;
}

void MainWindow::realtimefit()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[0];
    qreal key1 = iter[0];
#endif
    qreal value0 = iter[5]/PI;
    qreal value1 = iter[6]/PI;
    // add data to lines:
    ui->customplot->graph(0)->addData(key0, value0);
    ui->customplot->graph(2)->addData(key1, value1);
    // set data of dots:
    ui->customplot->graph(1)->clearData();
    ui->customplot->graph(1)->addData(key0, value0);
    ui->customplot->graph(3)->clearData();
    ui->customplot->graph(3)->addData(key1, value1);
    // remove data of lines that's outside visible range:
    ui->customplot->graph(0)->removeDataBefore(key0-8);
    ui->customplot->graph(2)->removeDataBefore(key1-8);
    //przeskalowanie
    ui->customplot->graph(0)->rescaleValueAxis(true);
    ui->customplot->graph(2)->rescaleValueAxis(true);

  //ui->customplot->yAxis->setRange(value0/2+value1/2, 2, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0+1, 8, Qt::AlignRight);
  ui->customplot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}

int MainWindow::setupyt(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=3;

  if(num!=a){
      return num;
  }

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
  customPlot->graph(0)->setAntialiasedFill(true);

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->graph(1)->setAntialiasedFill(true);

  customPlot->addGraph(); // red line
  customPlot->graph(2)->setPen(QPen(Qt::red));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssNone);

  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  ui->customplot->graph(0)->clearData();
  ui->customplot->graph(1)->clearData();
  ui->customplot->graph(2)->clearData();
  ui->customplot->graph(3)->clearData();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;
}

void MainWindow::realtimeyt()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[0];
    qreal key1 = iter[0];
#endif
    qreal value0 = -iter[2];
    qreal value1 = -iter[4];
    // add data to lines:
    ui->customplot->graph(0)->addData(key0, value0);
    ui->customplot->graph(2)->addData(key1, value1);
    // set data of dots:
    ui->customplot->graph(1)->clearData();
    ui->customplot->graph(1)->addData(key0, value0);
    ui->customplot->graph(3)->clearData();
    ui->customplot->graph(3)->addData(key1, value1);
    // remove data of lines that's outside visible range:
    ui->customplot->graph(0)->removeDataBefore(key0-300);
    ui->customplot->graph(2)->removeDataBefore(key1-300);
    //przeskalowanie
    ui->customplot->graph(0)->rescaleValueAxis(true);
    ui->customplot->graph(2)->rescaleValueAxis(true);

  //ui->customplot->yAxis->setRange(value0/2+value1/2+75, 150, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0+1, 8, Qt::AlignRight);
  ui->customplot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}

int MainWindow::setupxt(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=2;

  if(num!=a){
      return num;
  }

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));

  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
  customPlot->graph(0)->setAntialiasedFill(true);

  customPlot->addGraph(); // blue dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
  customPlot->graph(1)->setAntialiasedFill(true);

  customPlot->addGraph(); // red line
  customPlot->graph(2)->setPen(QPen(Qt::red));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssNone);

  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

  ui->customplot->graph(0)->clearData();
  ui->customplot->graph(1)->clearData();
  ui->customplot->graph(2)->clearData();
  ui->customplot->graph(3)->clearData();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;
}

void MainWindow::realtimext()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[0];
    qreal key1 = iter[0];
#endif
    qreal value0 = iter[1];
    qreal value1 = iter[3];
    // add data to lines:
    ui->customplot->graph(0)->addData(key0, value0);
    ui->customplot->graph(2)->addData(key1, value1);
    // set data of dots:
    ui->customplot->graph(1)->clearData();
    ui->customplot->graph(1)->addData(key0, value0);
    ui->customplot->graph(3)->clearData();
    ui->customplot->graph(3)->addData(key1, value1);
    // remove data of lines that's outside visible range:
    ui->customplot->graph(0)->removeDataBefore(key0-300);
    ui->customplot->graph(2)->removeDataBefore(key1-300);
    //przeskalowanie
    ui->customplot->graph(0)->rescaleValueAxis(true);
    ui->customplot->graph(2)->rescaleValueAxis(true);

  //ui->customplot->yAxis->setRange(value0/2+value1/2+75, 150, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0+1, 8, Qt::AlignRight);
  ui->customplot->replot();

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}

int MainWindow::setupxy(QCustomPlot *customPlot, int num)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  const int a=1;

  if(num!=a)
        return num;

  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimext()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeyt()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefit()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeomegat()));
  disconnect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimefifi()));

  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */

  customPlot->addGraph(); // red line
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsLine);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
  //customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);

  customPlot->addGraph(); // red dot
  customPlot->graph(1)->setPen(QPen(Qt::blue));
  customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);


  customPlot->addGraph(); // blue line
  customPlot->graph(2)->setPen(QPen(Qt::red));
  customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
  //customPlot->graph(0)->setSize
  //customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
  customPlot->graph(2)->setAntialiasedFill(true);

  /*
  customPlot->addGraph(); // red line
  customPlot->graph(1)->setPen(QPen(Qt::red));
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
  */

  customPlot->addGraph(); // blue dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);


  ui->customplot->graph(0)->clearData();
  ui->customplot->graph(1)->clearData();
  ui->customplot->graph(2)->clearData();
  ui->customplot->graph(3)->clearData();

/*
  customPlot->addGraph(); // red dot
  customPlot->graph(3)->setPen(QPen(Qt::red));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
*/
  //customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
  //customPlot->xAxis->setDateTimeFormat("mm:ss");
  //customPlot->xAxis->setAutoTickStep(false);
  //customPlot->xAxis->setTickStep(2);
  //customPlot->axisRect()->setupFullAxesBox();

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimexy()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible

  return a;

}

void MainWindow::realtimexy()
{

   QVector <qreal> ::iterator iter = wektor.begin();

  // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  double key = 0;
#else
    qreal time = iter[0];
    qreal key0 = iter[1];
    qreal key1 = iter[3];
#endif
  //static double lastPointKey = 0;
  //if (key-lastPointKey > 0.01) // at most add point every 10 ms
    qreal value0 = -iter[2]; //sin(key*1.6+cos(key*1.7)*2)*10 + sin(key*1.2+0.56)*20 + 26;
    qreal value1 = -iter[4];
    //double value1 = qCos(key); //sin(key*1.3+cos(key*1.2)*1.2)*7 + sin(key*0.9+0.26)*24 + 26;
    // add data to lines:
    ui->customplot->graph(0)->addData(key0, value0);
    ui->customplot->graph(2)->addData(key1, value1);
    // set data of dots:
    ui->customplot->graph(1)->clearData();
    ui->customplot->graph(1)->addData(key0, value0);
    ui->customplot->graph(3)->clearData();
    ui->customplot->graph(3)->addData(key1, value1);
    // remove data of lines that's outside visible range:
    ui->customplot->graph(0)->removeDataBefore(key0-300);
    ui->customplot->graph(2)->removeDataBefore(key1/2+key0/2-75);
    ui->customplot->graph(2)->removeDataAfter(key1/2+key0/2+75);
    // rescale value (vertical) axis to fit the current data:
    //ui->customplot->graph(0)->rescaleValueAxis(true);
    //ui->customplot->graph(1)->rescaleValueAxis(true);
    //lastPointKey = key;

  ui->customplot->yAxis->setRange(value0/2+value1/2+120, 200, Qt::AlignRight);
  // make key axis range scroll with the data (at a constant range size of 8):
  ui->customplot->xAxis->setRange(key0/2+key1/2+75, 150, Qt::AlignRight);
  ui->customplot->replot();

  //zoom, który nie działa tutaj...
  //ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  // calculate frames per second:
  static double lastFpsKey;
  static int frameCount;
  ++frameCount;
  if (time-lastFpsKey > 2) // average fps over 2 seconds
  {
    ui->statusBar->showMessage(
          QString("%1 FPS, Total Data points: %2")
          .arg(frameCount/(time-lastFpsKey), 0, 'f', 0)
          .arg(ui->customplot->graph(0)->data()->count()+ui->customplot->graph(2)->data()->count())
          , 0);
    lastFpsKey = time;
    frameCount = 0;
  }
}


/*
void MainWindow::setupSincScatterDemo(QCustomPlot *customPlot)
{
  demoName = "Sinc Scatter Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica",9));
  // set locale to english, so we get english decimal separator:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // add confidence band graphs:
  customPlot->addGraph();
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor(QColor(180,180,180));
  customPlot->graph(0)->setName("Confidence Band 68%");
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
  customPlot->addGraph();
  customPlot->legend->removeItem(customPlot->legend->itemCount()-1); // don't show two confidence band graphs in legend
  customPlot->graph(1)->setPen(pen);
  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
  // add theory curve graph:
  customPlot->addGraph();
  pen.setStyle(Qt::DashLine);
  pen.setWidth(2);
  pen.setColor(Qt::red);
  customPlot->graph(2)->setPen(pen);
  customPlot->graph(2)->setName("Theory Curve");
  // add data point graph:
  customPlot->addGraph();
  customPlot->graph(3)->setPen(QPen(Qt::blue));
  customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
  customPlot->graph(3)->setErrorType(QCPGraph::etNone);
  customPlot->graph(3)->setErrorPen(QPen(QColor(180,180,180)));
  customPlot->graph(3)->setName("Measurement");

  // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
  QVector<double> x0(250), y0(250);
  QVector<double> yConfUpper(250), yConfLower(250);
  for (int i=0; i<250; ++i)
  {
    x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
    y0[i] = sin(x0[i])/x0[i]; // sinc function
    yConfUpper[i] = y0[i]+0.15;
    yConfLower[i] = y0[i]-0.15;
    x0[i] *= 1000;
  }
  QVector<double> x1(50), y1(50), y1err(50);
  for (int i=0; i<50; ++i)
  {
    // generate a gaussian distributed random number:
    double tmp1 = rand()/(double)RAND_MAX;
    double tmp2 = rand()/(double)RAND_MAX;
    double r = sqrt(-2*log(tmp1))*cos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
    // set y1 to value of y0 plus a random gaussian pertubation:
    x1[i] = (i/50.0-0.5)*30+0.25;
    y1[i] = sin(x1[i])/x1[i]+r*0.15;
    x1[i] *= 1000;
    y1err[i] = 0.15;
  }
  // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
  customPlot->graph(0)->setData(x0, yConfUpper);
  customPlot->graph(1)->setData(x0, yConfLower);
  customPlot->graph(2)->setData(x0, y0);
  customPlot->graph(3)->setDataValueError(x1, y1, y1err);
  customPlot->graph(2)->rescaleAxes();
  customPlot->graph(3)->rescaleAxes(true);
  // setup look of bottom tick labels:
  customPlot->xAxis->setTickLabelRotation(30);
  customPlot->xAxis->setAutoTickCount(9);
  customPlot->xAxis->setNumberFormat("ebc");
  customPlot->xAxis->setNumberPrecision(1);
  customPlot->xAxis->moveRange(-10);
  // make top right axes clones of bottom left axes. Looks prettier:
  customPlot->axisRect()->setupFullAxesBox();
}


void MainWindow::setupScatterStyleDemo(QCustomPlot *customPlot)
{
  demoName = "Scatter Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setRowSpacing(-3);
  QVector<QCPScatterStyle::ScatterShape> shapes;
  shapes << QCPScatterStyle::ssCross;
  shapes << QCPScatterStyle::ssPlus;
  shapes << QCPScatterStyle::ssCircle;
  shapes << QCPScatterStyle::ssDisc;
  shapes << QCPScatterStyle::ssSquare;
  shapes << QCPScatterStyle::ssDiamond;
  shapes << QCPScatterStyle::ssStar;
  shapes << QCPScatterStyle::ssTriangle;
  shapes << QCPScatterStyle::ssTriangleInverted;
  shapes << QCPScatterStyle::ssCrossSquare;
  shapes << QCPScatterStyle::ssPlusSquare;
  shapes << QCPScatterStyle::ssCrossCircle;
  shapes << QCPScatterStyle::ssPlusCircle;
  shapes << QCPScatterStyle::ssPeace;
  shapes << QCPScatterStyle::ssCustom;

  QPen pen;
  // add graphs with different scatter styles:
  for (int i=0; i<shapes.size(); ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(sin(i*0.3)*100+100, sin(i*0.6+0.7)*100+100, sin(i*0.4+0.6)*100+100)); //wybiera różne kolory
    // generate data:
    QVector<double> x(10), y(10);
    for (int k=0; k<10; ++k)
    {
      x[k] = k/10.0 * 4*3.14 + 0.01; //dane punktów
      y[k] = 7*sin(x[k])/x[k] + (shapes.size()-i)*5;
    }
    customPlot->graph()->setData(x,y);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    // set scatter style:
    if (shapes.at(i) != QCPScatterStyle::ssCustom)
    {
      customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
    }
    else
    {
      QPainterPath customScatterPath;
      for (int i=0; i<3; ++i)
        customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
      customPlot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(), QColor(40, 70, 255, 50), 10));
    }
  }
  // set blank axis lines:
  customPlot->rescaleAxes();
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(false);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(false);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
}
*/

/*
void MainWindow::trajektoria(QCustomPlot *customPlot){
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
  QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
  demoName = "Real Time Data Demo";

  QCPCurve *trajektoria = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

  customPlot->addPlottable(trajektoria); // blue line
  trajektoria->setPen(QPen(Qt::blue));
  //trajektoria->setLineStyle(QCPGraph::lsNone);
  //trajektoria->setScatterStyle(QCPScatterStyle::ssDisc);
  trajektoria->setAntialiasedFill(true);

  customPlot->addGraph(); // blue dot
  customPlot->graph(0)->setPen(QPen(Qt::blue));
  customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
  customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);

  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

  // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(trajektoriaSlot()));
  dataTimer.start(50); // Interval 0 means to refresh as fast as possible


  connect(ui->widget, SIGNAL(dane(QVector<qreal> &)),this, SLOT(odbierzdane(QVector<qreal> &)));

}

void MainWindow::trajektoriaSlot(){

    QVector <qreal> ::iterator iter = wektor.begin();

    qreal key = iter[3];
    qreal value0 = -iter[4];

    //trajektoria = ui->customplot->plottable();

    trajektoria.addData(key, value0);

    ui->customplot->graph(0)->clearData();
    ui->customplot->graph(0)->addData(key, value0);

    trajektoria->removeDataBefore(key-300);

    ui->customplot->yAxis->setRange(value0+75, 150, Qt::AlignRight);
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customplot->xAxis->setRange(key+75, 150, Qt::AlignRight);
    ui->customplot->replot();

    //zoom, który nie działa tutaj...
    //ui->customplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
      ui->statusBar->showMessage(
            QString("%1 FPS, Total Data points: %2")
            .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
            .arg(ui->customplot->graph(0)->data()->count() )//+ui->customplot->graph(1)->data()->count())
            , 0);
      lastFpsKey = key;
      frameCount = 0;
    }
}

*/
