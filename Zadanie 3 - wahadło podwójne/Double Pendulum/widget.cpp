#include <QtGui>
#include "widget.h"
//#include "helper.h"
 #include "funkcje.h"

#define WIDTH 200
#define HEIGHT 10
#define PROMIEN 3
#define H 0.001
#define G 98.1
#define PI 3.14
#define SEPARATOR "  ;  "



 Widget::Widget(QWidget *parent)
     : QWidget(parent)
 {
     elapsed = 0;
     setFixedSize(400, 400);


     //helper
     background = QBrush(QColor(255, 255, 255));
     circlePen = QPen(Qt::black);
     circlePen.setWidth(3);
     textPen = QPen(Qt::black);
     circleBrush = QBrush(Qt::black);

     vector.resize(12);

     fi10 = 3.14/4;
     fi20 = -3.14/4;
     l1 = 200;
     l2 = 50;
     m1 = 10;
     m2 = 2;

     fi1 = fi10;
     fi2 = fi20;
     omega1 = 0;
     omega2 = 0;

     qreal
     x1 =  l1*sin(-fi1),
     y1 =  l1*cos(-fi1),
     x2 =  l1*sin(-fi1) + l2*sin(-fi2),
     y2 =  l1*cos(-fi1) + l2*cos(-fi2),
     A = m1/m2,
     B = l2/l1,
     C = G/l1;

     vector[0]=0.; //czas
     vector[1]=x1;
     vector[2]=y1;
     vector[3]=x2;
     vector[4]=y2;
     vector[5]=fi1;
     vector[6]=fi2;
     vector[7]=omega1;
     vector[8]=omega2;
     vector[9]=A;
     vector[10]=B;
     vector[11]=C;

     QFile file("wynik.txt");
     if (file.open(QFile::Append | QFile::Text))
     {
         QTextStream out(&file);
         out << "czas"<<SEPARATOR<<
                "x1"<<SEPARATOR<<
                "y1"<<SEPARATOR<<
                "x2"<<SEPARATOR<<
                "y2"<<SEPARATOR<<
                "fi1"<<SEPARATOR<<
                "fi2"<<SEPARATOR<<
                "omega1"<<SEPARATOR<<
                "omega2"<<SEPARATOR<<
                endl;
     }
     //file.close();


 }

 void Widget::animate()
 {
     elapsed = (elapsed + qobject_cast<QTimer*>(sender())->interval()) ;//% 1000;
     repaint();
 }

 void Widget::paintEvent(QPaintEvent *event)
 {
     QPainter painter;
     painter.begin(this);
     painter.setRenderHint(QPainter::Antialiasing);
     paint(&painter, event, elapsed);
     painter.end();
 }

 //sloty

 void Widget::setm1(const QString & newValue){
     m1 =newValue.toInt();
 }

 void Widget::setm2(const QString & newValue){
     m2 =newValue.toInt();
 }

 void Widget::setl1(const QString & newValue){
     l1 =newValue.toInt();
 }

 void Widget::setl2(const QString & newValue){
     l2 =newValue.toInt();
 }

 void Widget::setfi10(const QString & newValue){
     fi1 = newValue.toInt()*PI/180;
 }

 void Widget::setfi20(const QString & newValue){
     fi2 =newValue.toInt()*PI/180;
 }

 void Widget::reset(){
     omega1=0;
     omega2=0;
     elapsed=0;
     emit zmiana();
 }

  //helper

 void Widget::paint(QPainter *painter, QPaintEvent *event, int elapsed)
  {
      painter->setPen(circlePen);
      painter->setBrush(circleBrush);
      painter->fillRect(event->rect(), background);
      painter->save();

      A = m1/m2,
      B = l2/l1,
      C = G/l1;



      qreal k1,k2,k3,k4;
      int t = elapsed;


      int n = 50;
      for (int i = 0; i < n; ++i) {

          //algorytm Rungego-Kutty 4 rzędu :)
          //omega1 = y, t - brak zależności od czasu ?
          k1 = H * f1(fi1,fi2,omega1,omega2,A,B,C);
          k2 = H * f1(fi1,fi2,(omega1+k1*0.5),omega2,A,B,C);
          k3 = H * f1(fi1,fi2,(omega1+k2*0.5),omega2,A,B,C);
          k4 = H * f1(fi1,fi2,(omega1+k3),omega2,A,B,C);

          omega1+=((k1 + 2*k2 + 2*k3 + k4)/6);

          //omega2 = y, t - brak zależności od czasu ?
          k1 = H * f2(fi1,fi2,omega1,omega2,A,B,C);
          k2 = H * f2(fi1,fi2,omega1,(omega2+k1/2),A,B,C);
          k3 = H * f2(fi1,fi2,omega1,(omega2+k2/2),A,B,C);
          k4 = H * f2(fi1,fi2,omega1,(omega2+k3),A,B,C);

          omega2+=(k1 + 2*k2 + 2*k3 + k4)/6;

          fi2+=H*omega2;
          fi1+=H*omega1;
      }
      //fi1=fi1+3.14*2*t;
      qreal x1 =  l1*sin(-fi1),
            y1 =  l1*cos(-fi1),
            x2 =  l1*sin(-fi1) + l2*sin(-fi2),
            y2 =  l1*cos(-fi1) + l2*cos(-fi2);


      vector[0]=t*H*n/50;
      vector[1]=x1;
      vector[2]=y1;
      vector[3]=x2;
      vector[4]=y2;
      vector[5]=fi1;
      vector[6]=fi2;
      vector[7]=omega1;
      vector[8]=omega2;



      QFile file("wynik.txt");
      if (file.open(QFile::Append | QFile::Text))
      {
          QTextStream out(&file);
          out << QString::number(t*H*n/50,'f',2 )<<SEPARATOR<<
                 QString::number(x1,'f',2 )<<SEPARATOR<<
                 QString::number(y1,'f',2 )<<SEPARATOR<<
                 QString::number(x2,'f',2 )<<SEPARATOR<<
                 QString::number(y2,'f',2 )<<SEPARATOR<<
                 QString::number(fi1,'f',2 )<<SEPARATOR<<
                 QString::number(fi2,'f',2 )<<SEPARATOR<<
                 QString::number(omega1,'f',2 )<<SEPARATOR<<
                 QString::number(omega2,'f',2 )<<SEPARATOR<<
                 endl;
      }

      QPointF poczatkowy(WIDTH, HEIGHT);
      QPointF a(x1+WIDTH,y1+HEIGHT);
      QPointF b(x2+WIDTH,y2+ HEIGHT);
      QLineF line1(poczatkowy, a);
      QLineF line2(a,b);
      QLineF gora(0,HEIGHT,400,HEIGHT);

      circlePen = QPen(Qt::green);
      circlePen.setWidth(1);
      painter->drawEllipse(a,1,1);
      painter->drawEllipse(b,1,1);

      circlePen = QPen(Qt::black);
      circlePen.setWidth(3);
      //painter->drawText(QRect(50, 50, 100, 100), Qt::AlignCenter, QString::number(t*H*n/50,'f',2 ));

      //emit czasomierz(QString::number(t*H*n/50,'f',2));

      painter->drawLine(line1);
      painter->drawLine(line2);
      painter->drawLine(gora);
      painter->drawEllipse(poczatkowy,PROMIEN,PROMIEN);
      painter->drawEllipse(a,PROMIEN,PROMIEN);
      painter->drawEllipse(b,PROMIEN,PROMIEN);


      emit dane(vector);




      painter->restore();
  }
