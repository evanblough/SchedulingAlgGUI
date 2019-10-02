#include "graphdisplay.h"
#include "QPainter"
#include "QPaintEvent"

GraphDisplay::GraphDisplay(QWidget *parent) : QWidget(parent)
{
    this->update();

}
void GraphDisplay::paintEvent(QPaintEvent *event)
{
    int width = event->rect().width();
    int height = event->rect().height();
    QRect *rect = new QRect(0, 0, width/40, height/10);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::blue);
    painter.fillRect(*rect, Qt::red);
    painter.drawRect(*rect);
    painter.drawText(*rect, Qt::AlignCenter,
                      "T1");
}
