
#include <QtGui>
#include "helper.h"

#define WIDTH 150
#define HEIGHT 10
#define PROMIEN 3
#define H 0.001
#define G 9.81

 Helper::Helper()
 {
     background = QBrush(QColor(255, 255, 255));
     circlePen = QPen(Qt::black);
     circlePen.setWidth(3);
     textPen = QPen(Qt::black);
     circleBrush = QBrush(Qt::black);

     fi10 = -3.14/4;
     fi20 = 0;
     l1 = 100;
     l2 = 50;
     m1 = 1000;
     m2 = 10;
     A = m1/m2,
     B = l2/l1,
     C = G/l1;

     fi1 = fi10;
     fi2 = fi20;
     omega1 = 0;
     omega2 = 0;
     domega2 = 0;
     domega1 = 0;

     /*
     QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
     gradient.setColorAt(0.0, Qt::white);
     gradient.setColorAt(1.0, QColor(0xa6, 0xce, 0x39));

     background = QBrush(QColor(64, 32, 64));
     circleBrush = QBrush(gradient);
     circlePen = QPen(Qt::black);
     circlePen.setWidth(1);
     textPen = QPen(Qt::white);
     textFont.setPixelSize(50);
     */
 }

float f1( qreal fi1, qreal fi2, qreal omega1, qreal omega2, qreal A, qreal B, qreal C ){

    return ((-0.5*sin(2*(fi1-fi2))*omega1*omega1 +C*sin(fi2)*cos(fi1-fi2) - B*sin(fi1-fi2)*omega2*omega2 - (A+1)*C*sin(fi1))/(A+sin(fi1-fi2)*sin(fi1-fi2)));
}

float f2( qreal fi1, qreal fi2, qreal omega1, qreal omega2, qreal A, qreal B, qreal C ){

    return (((A+1)*sin(fi1-fi2)*omega1*omega1 - (A+1)*C*sin(fi2) + B/2 * sin(2*(fi1-fi2))*omega2*omega2 + (A+1)*C*sin(fi1*cos(fi1-fi2)))/(B*(A+sin(fi1-fi2)*sin(fi1-fi2))));
}


 void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
 {
     painter->setPen(circlePen);
     painter->setBrush(circleBrush);
     painter->fillRect(event->rect(), background);
     painter->save();

     qreal k1,k2,k3,k4;
     qreal t = elapsed;

     int n = 200;
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

     QPointF poczatkowy(WIDTH, HEIGHT);
     QPointF a(x1+WIDTH,y1+HEIGHT);
     QPointF b(x2+WIDTH,y2+ HEIGHT);
     QLineF line1(poczatkowy, a);
     QLineF line2(a,b);
     QLineF gora(0,HEIGHT,300,HEIGHT);

     circlePen = QPen(Qt::green);
     circlePen.setWidth(1);
     painter->drawEllipse(a,1,1);
     painter->drawEllipse(b,1,1);

     circlePen = QPen(Qt::black);
     circlePen.setWidth(3);
     painter->drawText(QRect(50, 50, 100, 100), Qt::AlignCenter, QString::number(t*H*n/50,'f',2 ));


     painter->drawLine(line1);
     painter->drawLine(line2);
     painter->drawLine(gora);
     painter->drawEllipse(poczatkowy,PROMIEN,PROMIEN);
     painter->drawEllipse(a,PROMIEN,PROMIEN);
     painter->drawEllipse(b,PROMIEN,PROMIEN);


     painter->restore();


     /*
     painter->fillRect(event->rect(), background);
     painter->translate(100, 100);

     painter->save();
     painter->setBrush(circleBrush);
     painter->setPen(circlePen);
     painter->rotate(elapsed * 0.030);

     qreal r = elapsed/1000.0;
     int n = 30;
     for (int i = 0; i < n; ++i) {
         painter->rotate(30);
         qreal radius = 0 + 120.0*((i+r)/n);
         qreal circleRadius = 1 + ((i+r)/n)*20;
         painter->drawEllipse(QRectF(radius, -circleRadius,
                                     circleRadius*2, circleRadius*2));
     }
     painter->restore();

     painter->setPen(textPen);
     painter->setFont(textFont);
     painter->drawText(QRect(-50, -50, 100, 100), Qt::AlignCenter, "Qt");
     */

 }


 /*Euler simply:
         omega1+=H*f1(fi1,fi2,omega1,omega2,A,B,C);

         omega2+=H*f2(fi1,fi2,omega1,omega2,A,B,C);

         fi2+=H*omega2;
         fi1+=H*omega1;
     }
     */
