 #ifndef WIDGET_H
 #define WIDGET_H

 #include <QWidget>
#include <QVector>

#include <QBrush>
#include <QFont>
#include <QPen>

class QPainter;
class QPaintEvent;

 class Widget : public QWidget
 {
     Q_OBJECT

 public:
     Widget(QWidget *parent);
     void paint(QPainter *painter, QPaintEvent *event, int elapsed);
     qreal fi10 ,
           fi20,
           l1 ,
           l2 ,
           m1,
           m2;

     qreal fi1,
           fi2,
           omega1,
           omega2;

     QVector<qreal> vector;



 public slots:
     void animate();
     void setm1(const QString &);
     void setm2(const QString &);
     void setl1(const QString &);
     void setl2(const QString &);
     void setfi10(const QString &);
     void setfi20(const QString &);
     void reset();


 signals:
     void zmiana();
     void dane(QVector<qreal> &);


 protected:
     void paintEvent(QPaintEvent *event);

 private:
     QBrush background;
     QBrush circleBrush;
     QFont textFont;
     QPen circlePen;
     QPen textPen;
     qreal     A,B,C;


     int elapsed;
 };

 #endif
