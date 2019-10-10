#include "graphdisplay.h"
#include "QPainter"
#include "QPaintEvent"

GraphDisplay::GraphDisplay(QWidget *parent) : QWidget(parent)
{
    this->update();

}
void GraphDisplay::paintEvent(QPaintEvent *event)
{
    int width = event->rect().width() /20;
    int height = event->rect().height() /10;
    this->draw_textbox(0, 0, width, height, Qt::red, Qt::black, "T1");

}
void GraphDisplay::draw_textbox(int x, int y, int width, int height, QColor background, QColor text_color, QString taskname ){
    QRect *rect = new QRect(x, y, width, height);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(text_color);
    painter.fillRect(*rect, background);
    painter.drawRect(*rect);
    painter.drawText(*rect, Qt::AlignCenter, "T1");
}
