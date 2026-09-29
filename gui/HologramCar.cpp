#include "HologramCar.h"

#include <QPainter>
HologramCar::HologramCar(QWidget *parent)
    : QWidget(parent),
      scanY(0),
      opacity(0.85),
      increasing(false)
{
    connect(&timer,
            &QTimer::timeout,
            this,
            &HologramCar::updateScan);

    timer.start(30);
}

void HologramCar::setPixmap(const QPixmap &pix)
{
    car = pix;
    update();
}

void HologramCar::updateScan()
{
    scanY++;

    if(scanY > height())
        scanY = 0;

    if(increasing)
    {
        opacity += 0.01;

        if(opacity >= 0.90)
            increasing = false;
    }
    else
    {
        opacity -= 0.01;

        if(opacity <= 0.70)
            increasing = true;
    }

    update();
}

void HologramCar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

  
    painter.drawPixmap(rect(), car);

  
    // Cyan transparent overlay
   

    painter.fillRect(
        rect(),
        QColor(0,180,255,40));

    // Horizontal hologram lines
    

    painter.setPen(QPen(QColor(120,220,255,35),1));

    for(int y=0; y<height(); y+=5)
    {
        painter.drawLine(0,y,width(),y);
    }

   
    // Moving scan line
    

    QLinearGradient gradient(
        0,
        scanY-20,
        0,
        scanY+20);

    gradient.setColorAt(0,QColor(0,255,255,0));
    gradient.setColorAt(0.5,QColor(120,255,255,220));
    gradient.setColorAt(1,QColor(0,255,255,0));

    painter.fillRect(
        QRect(0,scanY-20,width(),40),
        gradient);

   
    // Outer glow

    painter.setPen(QPen(QColor(80,220,255,90),3));

    painter.drawRect(rect().adjusted(2,2,-2,-2));
}